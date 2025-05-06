import ecosim  

model = ecosim.Model(  
    num_steps=50,  
    num_repetitions=5,  
    num_wolves=5,  
    num_rabbits=20,  
    num_cabbages=40,  
    width=100.0,  
    height=100.0,  
    aggressiveness=0.5  
)  
model.run()  
model.print_results()  
