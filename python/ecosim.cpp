#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Model.h"
#include "Area.h"
#include "Wolf.h"
#include "Rabbit.h"
#include "Cabbage.h"
#include "MapObject.h"
#include "Creature.h"
#include "Animal.h"
#include "Command.h"
#include "Invoker.h"

namespace py = pybind11;

// Макрос для экспорта символов
#if defined(_WIN32)
    #define EXPORT_SYMBOL __declspec(dllexport)
#else
    #define EXPORT_SYMBOL __attribute__((visibility("default")))
#endif

// Вспомогательные функции для получения позиций
py::tuple get_wolf_positions(Area& area) {
    std::vector<double> x, y;
    area.getWolfPositions(x, y);
    return py::make_tuple(x, y);
}

py::tuple get_rabbit_positions(Area& area) {
    std::vector<double> x, y;
    area.getRabbitPositions(x, y);
    return py::make_tuple(x, y);
}

py::tuple get_cabbage_positions(Area& area) {
    std::vector<double> x, y;
    area.getCabbagePositions(x, y);
    return py::make_tuple(x, y);
}

py::tuple get_model_wolf_positions(Model& model) {
    std::vector<double> x, y;
    model.getCurrentWolfPositions(x, y);
    return py::make_tuple(x, y);
}

py::tuple get_model_rabbit_positions(Model& model) {
    std::vector<double> x, y;
    model.getCurrentRabbitPositions(x, y);
    return py::make_tuple(x, y);
}

py::tuple get_model_cabbage_positions(Model& model) {
    std::vector<double> x, y;
    model.getCurrentCabbagePositions(x, y);
    return py::make_tuple(x, y);
}

// Инициализация классов
void init_mapobject(py::module& m) {
    py::class_<MapObject>(m, "MapObject")
        .def_property_readonly("x", &MapObject::getX, "Get X coordinate")
        .def_property_readonly("y", &MapObject::getY, "Get Y coordinate")
        .def("distance_to", &MapObject::distanceTo, "Calculate distance to another object");
}

void init_creature(py::module& m) {
    py::class_<Creature, MapObject>(m, "Creature")
        .def("get_energy", &Creature::getEnergy, "Get current energy")
        .def("is_alive", &Creature::isAlive, "Check if creature is alive")
        .def("should_reproduce", &Creature::shouldReproduce, "Check reproduction readiness");
}

void init_animal(py::module& m) {
    py::class_<Animal, Creature>(m, "Animal")
        .def("move", &Animal::move, "Move the animal")
        .def("get_energy_cost", &Animal::getEnergyCostPerUnit, "Get energy cost per movement unit")
        .def("get_view_radius", &Animal::getViewRadius, "Get visibility range")
        .def("get_catch_radius", &Animal::getCatchRadius, "Get catching distance");
}

void init_wolf(py::module& m) {
    py::class_<Wolf, Animal>(m, "Wolf")
        .def(py::init<double, double, double, double>(),
             py::arg("x"), py::arg("y"), py::arg("energy"), py::arg("aggressiveness"),
             "Create a new Wolf")
        .def_property_readonly("aggressiveness", &Wolf::getAggressiveness, "Get aggressiveness level")
        .def("hunt", &Wolf::willHunt, "Check if wolf will hunt")
        .def("action", &Wolf::action, "Perform wolf action");
}

void init_rabbit(py::module& m) {
    py::class_<Rabbit, Animal>(m, "Rabbit")
        .def(py::init<double, double, double>(),
             py::arg("x"), py::arg("y"), py::arg("energy"),
             "Create a new Rabbit")
        .def("action", &Rabbit::action, "Perform rabbit action");
}

void init_cabbage(py::module& m) {
    py::class_<Cabbage, Creature>(m, "Cabbage")
        .def(py::init<double, double, double>(),
             py::arg("x"), py::arg("y"), py::arg("energy"),
             "Create a new Cabbage")
        .def("action", &Cabbage::action, "Perform cabbage action");
}

void init_area(py::module& m) {
    py::class_<Area>(m, "Area")
        .def(py::init<double, double, int, int, int, double>(),
             py::arg("width"), py::arg("height"), 
             py::arg("num_wolves"), py::arg("num_rabbits"), 
             py::arg("num_cabbages"), py::arg("aggressiveness"),
             "Create simulation area")
        .def("step", &Area::step, "Advance simulation by one step")
        .def("get_wolf_count", &Area::getNumWolfs, "Get current wolf count")
        .def("get_rabbit_count", &Area::getNumRabbits, "Get current rabbit count")
        .def("get_cabbage_count", &Area::getNumCabbages, "Get current cabbage count")
        .def("is_alive", &Area::isSystemAlive, "Check if ecosystem is alive")
        .def("get_wolf_positions", &get_wolf_positions, "Get all wolf positions")
        .def("get_rabbit_positions", &get_rabbit_positions, "Get all rabbit positions")
        .def("get_cabbage_positions", &get_cabbage_positions, "Get all cabbage positions");
}

void init_model(py::module& m) {
    py::class_<Model>(m, "Model")
        .def(py::init<int, int, int, int, int, double, double, double>(),
             py::arg("num_steps"), py::arg("num_repetitions"),
             py::arg("num_wolves"), py::arg("num_rabbits"),
             py::arg("num_cabbages"), py::arg("width"),
             py::arg("height"), py::arg("aggressiveness"),
             "Create simulation model")
        .def("run", &Model::run, "Run full simulation")
        .def("get_wolf_positions", &get_model_wolf_positions, "Get current wolf positions")
        .def("get_rabbit_positions", &get_model_rabbit_positions, "Get current rabbit positions")
        .def("get_cabbage_positions", &get_model_cabbage_positions, "Get current cabbage positions")
        .def_property_readonly("wolf_positions_history", &Model::getWolfPositionsHistory, "Get wolf position history")
        .def_property_readonly("rabbit_positions_history", &Model::getRabbitPositionsHistory, "Get rabbit position history")
        .def_property_readonly("cabbage_positions_history", &Model::getCabbagePositionsHistory, "Get cabbage position history")
        .def("print_stats", &Model::printResults, "Print simulation statistics")
        .def_property_readonly("ecosystem_lifetimes", &Model::getEcosystemLifetimes, "Get lifetimes for each run")
        .def_property_readonly("average_energy_wolves", &Model::getAverageEnergyWolves, "Average wolves energy per run")
        .def_property_readonly("average_energy_rabbits", &Model::getAverageEnergyRabbits, "Average rabbits energy per run")
        .def_property_readonly("average_energy_cabbages", &Model::getAverageEnergyCabbages, "Average cabbages energy per run")
        .def("getCurrentWolfPositions", [](Model& model) {
            std::vector<double> x, y;
            model.getCurrentWolfPositions(x, y);
            return py::make_tuple(x, y);
        }, "Get current wolf positions")
        .def("getCurrentRabbitPositions", [](Model& model) {
            std::vector<double> x, y;
            model.getCurrentRabbitPositions(x, y);
            return py::make_tuple(x, y);
        }, "Get current rabbit positions")
        .def("getCurrentCabbagePositions", [](Model& model) {
            std::vector<double> x, y;
            model.getCurrentCabbagePositions(x, y);
            return py::make_tuple(x, y);
        }, "Get current cabbage positions");
}

EXPORT_SYMBOL PYBIND11_MODULE(ecosim, m) {
    m.doc() = "Ecosystem simulation module";

    init_mapobject(m);
    init_creature(m);
    init_animal(m);
    init_wolf(m);
    init_rabbit(m);
    init_cabbage(m);
    init_area(m);
    init_model(m);
}