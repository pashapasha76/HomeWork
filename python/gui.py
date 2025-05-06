import sys
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QSpinBox, QDoubleSpinBox, QTextEdit
)
import ecosim 

class EcosystemGUI(QMainWindow):
    def __init__(self):
        super().__init__()
        self.simulation = None
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Симулятор Экосистемы")
        self.setGeometry(100, 100, 600, 400)

        main_widget = QWidget()
        self.setCentralWidget(main_widget)
        layout = QVBoxLayout(main_widget)

        params_layout = QHBoxLayout()  
        self.params = {
            'num_steps': QSpinBox(), 
            'num_repetitions': QSpinBox(),
            'num_wolves': QSpinBox(),
            'num_rabbits': QSpinBox(),
            'num_cabbages': QSpinBox(),
            'width': QDoubleSpinBox(),
            'height': QDoubleSpinBox(),
            'aggressiveness': QDoubleSpinBox()
        }

        for name, widget in self.params.items():
            widget.setMinimum(1)
            widget.setMaximum(1000)
            params_layout.addWidget(QLabel(name.capitalize() + ":"))
            params_layout.addWidget(widget)
        
        self.params['aggressiveness'].setRange(0.0, 1.0)
        self.params['aggressiveness'].setSingleStep(0.1)
        self.params['width'].setRange(10.0, 1000.0)
        self.params['height'].setRange(10.0, 1000.0)

        layout.addLayout(params_layout)  

        self.btn_run = QPushButton("Запустить симуляцию")
        self.btn_run.clicked.connect(self.run_simulation)
        layout.addWidget(self.btn_run)

        self.output = QTextEdit()
        self.output.setReadOnly(True)
        layout.addWidget(self.output)

    def run_simulation(self):
        params = {k: w.value() for k, w in self.params.items()}

        self.simulation = ecosim.Model(**params)
        self.simulation.run()

        self.output.clear()
        self.output.append("=== Результаты симуляции ===")
        self.output.append(f"Среднее время жизни экосистемы: {self.simulation.ecosystem_lifetimes[-1]} шагов")
        self.output.append(f"Средняя энергия волков: {self.simulation.average_energy_wolves[-1]}")
        self.output.append(f"Средняя энергия кроликов: {self.simulation.average_energy_rabbits[-1]}")
        self.output.append(f"Средняя энергия капусты: {self.simulation.average_energy_cabbages[-1]}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = EcosystemGUI()
    window.show()
    sys.exit(app.exec_())