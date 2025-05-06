#include <cassert>
#include <vector>
#include <iostream>
#include "Model.h"
#include "Area.h"

void test_current_positions() {
    std::cout << "Running test_current_positions...\n";
    
    Model model(10, 1, 2, 3, 4, 100.0, 100.0, 0.5);
    
    std::vector<double> wolf_x, wolf_y;
    model.getCurrentWolfPositions(wolf_x, wolf_y);
    assert(wolf_x.empty() && wolf_y.empty() && "Initial wolf positions should be empty");
    
    std::vector<double> rabbit_x, rabbit_y;
    model.getCurrentRabbitPositions(rabbit_x, rabbit_y);
    assert(rabbit_x.empty() && rabbit_y.empty() && "Initial rabbit positions should be empty");
    
    std::vector<double> cabbage_x, cabbage_y;
    model.getCurrentCabbagePositions(cabbage_x, cabbage_y);
    assert(cabbage_x.empty() && cabbage_y.empty() && "Initial cabbage positions should be empty");
    
    model.run();
    
    model.getCurrentWolfPositions(wolf_x, wolf_y);
    assert(!wolf_x.empty() && !wolf_y.empty() && "Wolf positions should not be empty after run");
    assert(wolf_x.size() == wolf_y.size() && "Wolf X and Y positions count should match");
    
    model.getCurrentRabbitPositions(rabbit_x, rabbit_y);
    assert(!rabbit_x.empty() && !rabbit_y.empty() && "Rabbit positions should not be empty after run");
    assert(rabbit_x.size() == rabbit_y.size() && "Rabbit X and Y positions count should match");
    
    model.getCurrentCabbagePositions(cabbage_x, cabbage_y);
    assert(!cabbage_x.empty() && !cabbage_y.empty() && "Cabbage positions should not be empty after run");
    assert(cabbage_x.size() == cabbage_y.size() && "Cabbage X and Y positions count should match");
    
    std::cout << "test_current_positions passed!\n";
}

void test_positions_history() {
    std::cout << "Running test_positions_history...\n";
    
    const int STEPS = 5;
    Model model(STEPS, 1, 2, 3, 4, 100.0, 100.0, 0.5);
    model.run();
    
    const auto& wolf_history = model.getWolfPositionsHistory();
    const auto& rabbit_history = model.getRabbitPositionsHistory();
    const auto& cabbage_history = model.getCabbagePositionsHistory();
    
    assert(wolf_history.size() == STEPS && "Wolf history size mismatch");
    assert(rabbit_history.size() == STEPS && "Rabbit history size mismatch");
    assert(cabbage_history.size() == STEPS && "Cabbage history size mismatch");
    
    for (const auto& positions : wolf_history) {
        assert(positions.size() % 2 == 0 && "Wolf positions should be pairs of coordinates");
        assert(!positions.empty() && "Wolf positions should not be empty");
    }
    
    for (const auto& positions : rabbit_history) {
        assert(positions.size() % 2 == 0 && "Rabbit positions should be pairs of coordinates");
        assert(!positions.empty() && "Rabbit positions should not be empty");
    }
    
    for (const auto& positions : cabbage_history) {
        assert(positions.size() % 2 == 0 && "Cabbage positions should be pairs of coordinates");
        assert(!positions.empty() && "Cabbage positions should not be empty");
    }
    
    std::vector<double> current_wolf_x, current_wolf_y;
    model.getCurrentWolfPositions(current_wolf_x, current_wolf_y);
    
    const auto& last_wolf = wolf_history.back();
    assert(last_wolf.size() == current_wolf_x.size() * 2 && "Last wolf history mismatch");
    for (size_t i = 0; i < current_wolf_x.size(); ++i) {
        assert(last_wolf[i*2] == current_wolf_x[i] && "Wolf X coordinate mismatch");
        assert(last_wolf[i*2+1] == current_wolf_y[i] && "Wolf Y coordinate mismatch");
    }
    
    std::cout << "test_positions_history passed!\n";
}

void test_empty_world() {
    std::cout << "Running test_empty_world...\n";
    
    Model model(10, 1, 0, 0, 0, 100.0, 100.0, 0.5);
    model.run();
    
    std::vector<double> wolf_x, wolf_y;
    model.getCurrentWolfPositions(wolf_x, wolf_y);
    assert(wolf_x.empty() && wolf_y.empty() && "Wolf positions should be empty in empty world");
    
    std::vector<double> rabbit_x, rabbit_y;
    model.getCurrentRabbitPositions(rabbit_x, rabbit_y);
    assert(rabbit_x.empty() && rabbit_y.empty() && "Rabbit positions should be empty in empty world");
    
    std::vector<double> cabbage_x, cabbage_y;
    model.getCurrentCabbagePositions(cabbage_x, cabbage_y);
    assert(cabbage_x.empty() && cabbage_y.empty() && "Cabbage positions should be empty in empty world");
    
    const auto& wolf_history = model.getWolfPositionsHistory();
    const auto& rabbit_history = model.getRabbitPositionsHistory();
    const auto& cabbage_history = model.getCabbagePositionsHistory();
    
    for (const auto& positions : wolf_history) {
        assert(positions.empty() && "Wolf history should be empty in empty world");
    }
    
    for (const auto& positions : rabbit_history) {
        assert(positions.empty() && "Rabbit history should be empty in empty world");
    }
    
    for (const auto& positions : cabbage_history) {
        assert(positions.empty() && "Cabbage history should be empty in empty world");
    }
    
    std::cout << "test_empty_world passed!\n";
}

int main() {
    std::cout << "Starting position tests...\n";
    
    test_current_positions();
    test_positions_history();
    test_empty_world();
    
    std::cout << "All position tests passed successfully!\n";
    return 0;
}