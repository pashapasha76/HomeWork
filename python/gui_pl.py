import sys
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QSpinBox, QDoubleSpinBox, QTextEdit, QMessageBox
)
from pyswip import Prolog
import ecosim 

class EcosystemGUI(QMainWindow):
    def __init__(self):
        super().__init__()
        self.simulation = None
        self.prolog = Prolog()
        self.init_prolog_kb()
        self.initUI()

    def init_prolog_kb(self):
        try:
            # Очищаем предыдущие данные
            list(self.prolog.query("retractall(position(_, _, _))"))
        
            # Загружаем правила по одному через consult
            rules = """
                :- dynamic position/3.
                :- dynamic cluster/4.

                cluster(Type, X, Y, Size) :- 
                    findall((X1, Y1), position(Type, X1, Y1), Positions),
                    cluster_points(Positions, [], Clusters, 5.0, 3),
                    member((X, Y, Size), Clusters).

                cluster_points([], Clusters, Clusters, _, _).

                cluster_points([(X,Y)|Ps], Acc, Clusters, Radius, MinSize) :- 
                    (member((CX, CY, CSize), Acc),
                        distance((X,Y), (CX,CY), D),
                        D =< Radius
                    ->  
                        NewSize is CSize + 1,
                        NewCX is (CX * CSize + X) / NewSize,
                        NewCY is (CY * CSize + Y) / NewSize,
                        select((CX, CY, CSize), Acc, TempAcc),
                        NewAcc = [(NewCX, NewCY, NewSize) | TempAcc]
                    ;   
                        NewAcc = [(X, Y, 1) | Acc]
                    ),
                    cluster_points(Ps, NewAcc, Clusters, Radius, MinSize).

                distance((X1, Y1), (X2, Y2), D) :- 
                    DX is X1 - X2,
                    DY is Y1 - Y2,
                    D is sqrt(DX*DX + DY*DY).
            """
        
            # Сохраняем правила во временный файл
            with open('temp_rules.pl', 'w') as f:
                f.write(rules)
            
            # Загружаем из файла
            list(self.prolog.query(f"consult('temp_rules.pl')"))
        
            print("База знаний Prolog успешно инициализирована")
        
        except Exception as e:
            print(f"Ошибка инициализации Prolog: {str(e)}")
            QMessageBox.critical(self, "Ошибка Prolog", 
            f"Не удалось инициализировать базу знаний:\n{str(e)}")

    def initUI(self):
        self.setWindowTitle("Симулятор Экосистемы с Prolog-анализом")
        self.setGeometry(100, 100, 800, 600)

        main_widget = QWidget()
        self.setCentralWidget(main_widget)
        layout = QVBoxLayout(main_widget)

        # Панель параметров
        params_layout = QHBoxLayout()
        self.params = {
            'num_steps': (QSpinBox(), (1, 10000)),
            'num_repetitions': (QSpinBox(), (1, 100)),
            'num_wolves': (QSpinBox(), (1, 100)),
            'num_rabbits': (QSpinBox(), (1, 200)),
            'num_cabbages': (QSpinBox(), (1, 500)),
            'width': (QDoubleSpinBox(), (10.0, 1000.0)),
            'height': (QDoubleSpinBox(), (10.0, 1000.0)),
            'aggressiveness': (QDoubleSpinBox(), (0.0, 1.0))
        }

        for name, (widget, (min_val, max_val)) in self.params.items():
            widget.setMinimum(min_val)
            widget.setMaximum(max_val)
            if isinstance(widget, QDoubleSpinBox):
                widget.setSingleStep(0.1 if name == 'aggressiveness' else 10.0)
            params_layout.addWidget(QLabel(name.replace('_', ' ').capitalize() + ":"))
            params_layout.addWidget(widget)
        
        layout.addLayout(params_layout)

        # Кнопки управления
        btn_layout = QHBoxLayout()
        self.btn_run = QPushButton("🔄 Запустить симуляцию")
        self.btn_run.setStyleSheet("background-color: #4CAF50; color: white;")
        self.btn_run.clicked.connect(self.run_simulation)
        btn_layout.addWidget(self.btn_run)
        
        self.btn_analyze = QPushButton("🔍 Анализировать кластеры")
        self.btn_analyze.setStyleSheet("background-color: #2196F3; color: white;")
        self.btn_analyze.clicked.connect(self.analyze_clusters)
        self.btn_analyze.setEnabled(False)
        btn_layout.addWidget(self.btn_analyze)
        
        layout.addLayout(btn_layout)

        # Вывод результатов
        self.output = QTextEdit()
        self.output.setStyleSheet("""
            QTextEdit {
                background-color: #f8f9fa;
                border: 1px solid #ddd;
                font-family: Consolas, monospace;
                font-size: 12px;
            }
        """)
        self.output.setReadOnly(True)
        layout.addWidget(self.output)

    def run_simulation(self):
        try:
            params = {k: w.value() for k, (w, _) in self.params.items()}
            
            self.simulation = ecosim.Model(**params)
            self.simulation.run()
            
            self.output.clear()
            self.output.append("=== РЕЗУЛЬТАТЫ СИМУЛЯЦИИ ===")
            self.output.append(f"🔹 Среднее время жизни: {self.simulation.ecosystem_lifetimes[-1]} шагов")
            self.output.append(f"🐺 Энергия волков: {self.simulation.average_energy_wolves[-1]:.2f}")
            self.output.append(f"🐇 Энергия кроликов: {self.simulation.average_energy_rabbits[-1]:.2f}")
            self.output.append(f"🥬 Энергия капусты: {self.simulation.average_energy_cabbages[-1]:.2f}")
            
            self.btn_analyze.setEnabled(True)
            
        except Exception as e:
            self.output.append(f"❌ Ошибка при запуске симуляции: {str(e)}")

    def analyze_clusters(self):
        if not self.simulation:
            self.output.append("⚠ Сначала запустите симуляцию!")
            return
            
        try:
            # Очищаем предыдущие данные
            list(self.prolog.query("retractall(position(_, _, _))"))
            
            # Получаем позиции из симуляции
            
            wolf_x, wolf_y = self.simulation.getCurrentWolfPositions()
            rabbit_x, rabbit_y = self.simulation.getCurrentRabbitPositions()
            cabbage_x, cabbage_y = self.simulation.getCurrentCabbagePositions()
            
            # Загружаем данные в Prolog
            for x, y in zip(wolf_x, wolf_y):
                self.prolog.assertz(f"position(wolf, {x}, {y})")
                
            for x, y in zip(rabbit_x, rabbit_y):
                self.prolog.assertz(f"position(rabbit, {x}, {y})")
                
            for x, y in zip(cabbage_x, cabbage_y):
                self.prolog.assertz(f"position(cabbage, {x}, {y})")
            
            # Анализируем кластеры
            self.output.append("\n=== АНАЛИЗ КЛАСТЕРОВ ===")
            
            # Для волков
            wolf_clusters = list(self.prolog.query("cluster(wolf, X, Y, Size)"))
            self.output.append(f"\n🐺 Кластеры волков (найдено {len(wolf_clusters)}):")
            for cluster in wolf_clusters:
                self.output.append(f"- Центр: ({cluster['X']:.1f}, {cluster['Y']:.1f}), Размер: {cluster['Size']}")
            
            # Для кроликов
            rabbit_clusters = list(self.prolog.query("cluster(rabbit, X, Y, Size)"))
            self.output.append(f"\n🐇 Кластеры кроликов (найдено {len(rabbit_clusters)}):")
            for cluster in rabbit_clusters:
                self.output.append(f"- Центр: ({cluster['X']:.1f}, {cluster['Y']:.1f}), Размер: {cluster['Size']}")
            
            # Для капусты
            cabbage_clusters = list(self.prolog.query("cluster(cabbage, X, Y, Size)"))
            self.output.append(f"\n🥬 Кластеры капусты (найдено {len(cabbage_clusters)}):")
            for cluster in cabbage_clusters:
                self.output.append(f"- Центр: ({cluster['X']:.1f}, {cluster['Y']:.1f}), Размер: {cluster['Size']}")
            
        except Exception as e:
            self.output.append(f"\n❌ Ошибка анализа: {str(e)}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    
    # Установка стиля
    app.setStyleSheet("""
        QMainWindow {
            background-color: #f5f5f5;
        }
        QPushButton {
            padding: 8px;
            border-radius: 4px;
            font-weight: bold;
        }
        QLabel {
            font-weight: bold;
        }
    """)
    
    window = EcosystemGUI()
    window.show()
    sys.exit(app.exec_())