import unittest
import ecosim

class TestEcoSim(unittest.TestCase):
    def setUp(self):
        self.model_params = {
            "num_steps": 50,
            "num_repetitions": 3,
            "num_wolves": 2,
            "num_rabbits": 4,
            "num_cabbages": 6,
            "width": 100.0,
            "height": 100.0,
            "aggressiveness": 0.5
        }

    def test_objects_creation(self):
        area = ecosim.Area(100.0, 100.0, 1, 2, 3, 0.5)
        self.assertEqual(area.get_wolf_count(), 1)
        self.assertEqual(area.get_rabbit_count(), 2)
        self.assertEqual(area.get_cabbage_count(), 3)

    def test_model_run(self):
        model = ecosim.Model(**self.model_params)
        model.run()
        self.assertEqual(
            len(model.wolf_positions_history), 
            self.model_params["num_repetitions"]
        )

    def test_edge_cases(self):  
        empty_model = ecosim.Model(0, 0, 0, 0, 0, 0.0, 0.0, 0.0)
        empty_model.run()
        self.assertEqual(len(empty_model.ecosystem_lifetimes), 0)

if __name__ == '__main__':
    unittest.main(verbosity=2)