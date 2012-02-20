package fishPond;

import javax.swing.event.*;
import cmsc131Utilities.Random131;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * THIS CLASS IS IMPLEMENTED FOR YOU -- DO NOT MODIFY IT!
 * <p>                                             
 * The Controller class contains main(), which instantiates the Controller.       
 * <p>                                                                                
 * The constructor of the Controller instantiates the Model and the View.  (The     
 * Model is re-instantiated each time the user re-starts the simulation by          
 * pressing a button.)  The constructor of the Controller starts the simulation.                       
 *                                                                                 
 * @author Fawzi Emad, Copyright(C) 2005                                           
 */
public class Controller {
	
	/* The other two components of the M-V-C pattern */
	private Model model;
	private View view;
	
	/* Amount of time to wait between displaying frames (milliseconds) */
	private int simulationDelay;
	
	/* Values to copy into model each time simulation is restarted */
	private int rows = 30, cols = 40, fishCount = 40, rockCount = 250, plantCount = 50;
	
	/* Set to true when a button has been pressed. Controller waits until the 
	 * current frame has been processed before instantiating a new Model.  */
	private boolean newModelRequested;
	
	/* Value used to seed random number generator before each run of the
	 * simulation.  This value is changed if "New Pond" button is pressed.
	 * If "restart" button is pressed, this value remains the same as it was
	 * in the previous run. */
	private long seedForNextRun;
	
	/** Controller is normally only instantiated ONCE. The constructor seeds the
	 *  random number generator, creates the Model and the View, and runs the
	 *  simulation. */
	public Controller() {
		
		/* Start with a random seed.  If debugging, consider temporarily changing
		 * this line to seedForNextRun = CONSTANT, for some constant value. */
		seedForNextRun = Random131.getRandomInteger(123456789);
		
		/* Instantiate the other components of the M-V-C pattern */
		createNewModelAndView();
		
		/* Enter the infinite loop that makes it all work! */
		runSimulation();
	}
	
	/* Instantiate the other components of M-V-C design pattern and instantiate 
	 * and register listeners for the controls in the View.  This method is 
	 * called only once. */
	private void createNewModelAndView() {
		
		/* Seed random number generator. */
		Random131.setDeterministic(seedForNextRun);
		
		/* Create Model and View */
		model = new Model(rows, cols, rockCount, fishCount, plantCount);
		view = new View(new Model(model), rows, cols, rockCount, fishCount, plantCount);
		
		/* Instantiate and register listeners with controls in the View */
		view.registerSliderListener(new MySliderListener());
		view.registerRestartButtonListener(new RestartButtonListener());
		view.registerDifferentPondButtonListener(new DifferentPondButtonListener());
		
		/* Calculate delay time by reading slider position */
		setSimulationDelay();
	}
	
	/* When user re-starts the simulation, this method re-initializes the model
	 * and registers it with the View. This method is run in the thread that
	 * detected a button click. */
	private void createNewModel() {
		
		/* Seed random number generator.  If "New Pond" was pressed, the seed will
		 * be different from last time; if "Restart" was pressed the old seed will
		 * be used again. */
		Random131.setDeterministic(seedForNextRun);
		
		model = new Model(rows, cols, rockCount, fishCount, plantCount);
		
		/* View is notified that there is new data */
		view.updateYourself(new Model(model));
		
		/* Resize the view. */
		view.rePack();
	}
	
	/* Enters infinite loop that controls the simulation */
	private void runSimulation() {
		
		while(true){
			
			/* If user has pressed a button, we'll start a new Model. */
			if (newModelRequested) {
				createNewModel();
				newModelRequested = false;
			}
			
			model.turnFish();          // Fish turn if about to hit rocks 
			notifyViewAndPause();      // Show new fish orientation in GUI
			model.moveFish();          // Fish move, eat plants, eat other fish
			model.shrinkFish();        // Fish get smaller
			model.removeDeadFish();    // Remove fish of size 0 or less
			model.removeDeadPlants();  // Remove plants of size 0 or less
			model.growPlants();        // Plants get bigger
			doSanityChecks();          // Look for inconsistent state of the model
			notifyViewAndPause();      // Show new positions in GUI
			model.fishExplosions();    // Big fish explode into smaller ones
			model.plantExplosions();   // Big plants explode into smaller ones
			doSanityChecks();          // Look for inconsistent state of the model			
			notifyViewAndPause();      // Show explosions in GUI
		}
	}
	
	/* Notify View that model has been modified.  Pause for a while. */
	private void notifyViewAndPause() {
		
		/* Notify View that Model has changed.  View receives a COPY of the model 
		 * so that the GUI-drawing-thread is not drawing the picture while we are 
		 * simultaneously modifying the data! */
		view.updateYourself(new Model(model));
		
		/* Wait a while before doing the next frame */
		try {
			Thread.sleep(simulationDelay + 1);  // Why does +1 make it faster????
		}
		catch(InterruptedException e) { // no worries	
		}
	}
	
	/* This method checks to see if you have messed up data with two fish in the same 
	 * place; two plants in the same place; or a fish/plant over a rock!  This method 
	 * is intended as a development tool. */
	private void doSanityChecks() {
		
		ArrayList<Fish> fish = model.getFish();
		ArrayList<Plant> plants = model.getPlants();
		
		/* This checks if you have an inconsistant model with more than one live
		 * fish in the same spot.  This should never be the case! */
		Iterator<Fish> i = fish.iterator();
		while(i.hasNext()) {
			Fish curr = i.next();
			Iterator<Fish> j = fish.iterator();
			while(j.hasNext()) {
				Fish curr2 = j.next();
				if (curr != curr2)
					if (curr.isAlive() && curr2.isAlive())
						if (curr.getRow() == curr2.getRow() && curr.getCol() == curr2.getCol()) 
							throw new IllegalFishPositionException(IllegalFishPositionException.TWO_FISH_IN_ONE_PLACE);	
			}
		}
		
		/* This checks if you have an inconsistant model with more than one live
		 * plant in the same place.  This should never be the case! */
		Iterator<Plant> j = plants.iterator();
		while(j.hasNext()) {
			Plant curr = j.next();
			Iterator<Plant> k = plants.iterator();
			while(k.hasNext()) {
				Plant curr2 = k.next();
				if (curr != curr2)
					if (curr.getRow() == curr2.getRow() && curr.getCol() == curr2.getCol())
						throw new IllegalPlantPositionException(IllegalPlantPositionException.TWO_PLANTS_IN_ONE_PLACE);
			}
		}
		
		/* This checks if you have put any fish over a rock */
		i = fish.iterator();
		while(i.hasNext()) {
			Fish curr = i.next();
			if (model.getShape(curr.getRow(), curr.getCol()) != Model.WATER) {
				throw new IllegalFishPositionException(IllegalFishPositionException.FISH_OVER_ROCK);
			}
		}
		
		/* This checks if you have put any plant over a rock */
		j = plants.iterator();
		while(j.hasNext()) {
			Plant curr = j.next();
			if (model.getShape(curr.getRow(), curr.getCol()) != Model.WATER) {
				throw new IllegalPlantPositionException(IllegalPlantPositionException.PLANT_OVER_ROCK);
			}
		}
	}
	
	/* Listener for the slider in the View */
	private class MySliderListener implements ChangeListener{
		
		/* Callback that runs when slider has been moved */
		public void stateChanged(ChangeEvent e) {
			setSimulationDelay();
		}
	}
	
	/* Listener for the Restart Button in the View */
	private class RestartButtonListener implements ActionListener {
		
		/* Callback that runs when button is clicked */
		public void actionPerformed(ActionEvent e) {
			newModelRequested = true;  // same random seed, same parameters
		}
	}
	
	/* Listener for the "New Pond" button in the View */
	private class DifferentPondButtonListener implements ActionListener {
		
		/* Callback that runs when button is pressed */
		public void actionPerformed(ActionEvent e) {
			readFieldsFromView();  // use parameters entered into GUI for next run
			seedForNextRun = Random131.getRandomInteger(123456789); // different seed
			newModelRequested = true;
		}
	}
	
	/* Calculates delay time (milliseconds) based on slider position (0-100) */
	private void setSimulationDelay() {
		simulationDelay = 100 - view.getSliderPosition();
		simulationDelay *= simulationDelay / 10;
	}
	
	/* Reads numerical fields from the View so that they can be used in
	 * the next run of the simulation. */
	private void readFieldsFromView() {
		rows = view.getRows();
		cols = view.getCols();
		rockCount = view.getRockCount();
		fishCount = view.getFishCount();
		plantCount = view.getPlantCount();
	}
	
	 /**
	 * Driver that simply instantiates the Controller. 
	 */
	public static void main(String[] args) {
		
		new Controller();
	}
	
}