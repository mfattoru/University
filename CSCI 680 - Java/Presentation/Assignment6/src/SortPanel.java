/************************************************************
 *                                                          *
 *  CSCI 470/680          Assignment 6         Summer 2018  *
 *                                                          *
 *  Programmer: Michele Fattoruso - Z1840898                *
 *                                                          *
 *  Date Due:   Tuesday, August 7, 2018 11:59 PM            *
 *                                                          *
 *  Purpose:    Java Concurrency and Animation              *
 *                                                          *
 ***********************************************************/

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JPanel;

public class SortPanel extends JPanel{

	//variable used to serialize the object
	private static final long serialVersionUID = 1L;
	//Time that the thread sleep after each swap, used to slow down the 
	//sorting animation
	private final static int THREAD_SLEEP = 10;
	//Button used to start the sorting process
	private JButton sortButton;
	//Button used to populate the array
	private JButton populateButton;
	//JComboBox used to choose the sorting method to apply
	private JComboBox<String> sortSelector;
	
	//Panel used to graphically display the sorting process
	private SortAnimationPanel sortCanvas;
	//Array containing the element to sort
	private int[] array;
	
	public SortPanel() {
		//Array containing the sorting method, used to populate the jcombobox
		String[] elements = {"Insertion sort","Quick sort", "Bubble sort"};
		//Initializing the array to null
		array = null;
		//Instantiating the sorting button
		sortButton = new JButton("Sort");
		//and setting it to disabled as default, as the array hasn't been populated yet
		sortButton.setEnabled(false);
		//instantiation the populate button
		populateButton = new JButton("Populate Array");
		//Instantiating the JComboBox, filling it with the elements declared in the elements array
		sortSelector = new JComboBox<String>(elements);
		//Instantiation a SortAnimationPanel
		sortCanvas = new SortAnimationPanel();
		
		//Adding an action listener to the populate button
		populateButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				//getting the dimension of the SortAnimationPanel
				Dimension dim = sortCanvas.getPreferredSize();
				//Getting it's width and height
				int maxValue = dim.height;
				int numOfValues = dim.width;
				//Initializing a random object, to use later to generate random integers
				Random rand = new Random();
				//initializing an array to contain a number of integers equals to the width of the SortAnimationPanel
				array = new int[numOfValues];
				
				//Populating the array with random integers
				for(int i=0;i<numOfValues;i++) {
					array[i] = rand.nextInt(maxValue);
				}
				//Once the array is populated we can enable the sorting button
				sortButton.setEnabled(true);
				//and display the values on the SortAnimationPanel
				sortCanvas.repaint();
			}
		});
		
		//Adding an action listener for the sorting button
		sortButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				//once the sorting is started, we can't re-populate the array until the sorting has completed
				populateButton.setEnabled(false);
				//Set the sorting method in the SortAnimationPanel to be equal to the one selected in the JComboBox
				sortCanvas.setSortingMethod(sortSelector.getSelectedIndex());
				//Declaring a new thread, that will run the sort on the array
				Thread t = new Thread(sortCanvas);
				//start the thread
				t.start();
			}
			
		});

		//adding the SortAnimationPanel to the JPanel
		add(sortCanvas);
		//adding the populate button to the JPanel
		add(populateButton);
		//adding the sortButton to the JPanel
		add(sortButton);
		//Adding the sort selector JComboBox to the JPanel
		add(sortSelector);
		
	}
	
	private class SortAnimationPanel extends JPanel implements Runnable{
		//Variable user for the serializable object
		private static final long serialVersionUID = 1L;
		//Constant associated to the index returned by the JComboBox index
		public static final int INSERTION_SORT = 0;
		public static final int QUICK_SORT = 1;
		public static final int BUBBLE_SORT = 2;
		
		//Sort method setted in the panel
		private int sortMethod;

		//Method used to set the desired sorting method for the SortAnimationPanel
		public void setSortingMethod(int sortMethod) throws IllegalArgumentException {
			//set the sortMethod as InsertionSOrt
			if(sortMethod == INSERTION_SORT) {
				this.sortMethod = INSERTION_SORT;
				System.out.println("selected Insert "+ sortMethod);
			}else if(sortMethod == QUICK_SORT){  //as QuickSort
				this.sortMethod = QUICK_SORT;
				System.out.println("selected quick "+ sortMethod);
			}else if(sortMethod == BUBBLE_SORT){ //As BubbleSort
				this.sortMethod = BUBBLE_SORT;
				System.out.println("selected bububle "+ sortMethod);
			}else {  //if the selected method doesn't exist, the throw an esception
				throw new IllegalArgumentException("the selected sort method doesn't exist");
			}
		}
		
		//Constructor
		public SortAnimationPanel() {
			//set the background to the JPanel 
			setBackground(Color.WHITE);
			//Set the size of the panel
			setPreferredSize(new Dimension(730,600));
		}
		
		//Override the run method of the runnable interface
		@Override
		public void run() {
			//When starting to run, disable the populate button
			sortButton.setEnabled(false);
			//Run a sorting algorithm based on the one chosen from the JComboBox
			if(sortMethod==INSERTION_SORT) {
				insertionSort(array);
			}else if(sortMethod==QUICK_SORT){
				quickSort(array);
			}else if(sortMethod == BUBBLE_SORT){
				bubbleSort(array);
			}
			//Once the sorting finished, re-enable the populate button
			populateButton.setEnabled(true);
		}


		//Override the paintComponent to display the array as vertical lines of 1 pixel 
		//for each element of the array, with an height equal to the value of the cell
		@Override
		public void paintComponent(Graphics g) {
			//call the superclass paint component
			super.paintComponent(g);
			//get the height of the panel
			int height = this.getHeight();
			//Set the color of the graphic to  blue
			g.setColor(Color.BLUE);
			
			//If the array is not null, so f it has been populated
			if(array != null) {
				//draw vertical lines starting from the bottom left corner
				for( int i = 0; i < array.length ; i++ ){
					g.drawLine(i, height, i, height-array[i]);
				}
			}
		}
		
		//Bubble sort algorithm
		public void bubbleSort(int arr[]){
	        int n = arr.length;
	        for (int i = 0; i < n-1; i++) {
	            for (int j = 0; j < n-i-1; j++) {
	                if (arr[j] > arr[j+1]){
	                    // swap temp and arr[i]

	                    int temp = arr[j];
	                    arr[j] = arr[j+1];
	                    arr[j+1] = temp;
	                    
	                    //after a swap, repaint the panel so we can show the animation
		                repaint();
		                //pause the thread to slow down the animation
		                try {
							Thread.sleep(THREAD_SLEEP);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
	                }
	                
	    		}
			}	
	        
	    }
		
		//Insertion sort algorithm
		public void insertionSort(int arr[]){
	        int n = arr.length;
	        for (int i=1; i<n; ++i){
	            int key = arr[i];
	            int j = i-1;
	 
	            /* Move elements of arr[0..i-1], that are
	               greater than key, to one position ahead
	               of their current position */
	            while (j>=0 && arr[j] > key){
	                arr[j+1] = arr[j];
	                j = j-1;
	                
	                //after a swap, repaint the panel so we can show the animation
	                repaint();
	                //pause the thread to slow down the animation
		            try {
						Thread.sleep(THREAD_SLEEP);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
	            }
	            arr[j+1] = key;
	            
	            
	        }
	    }
		
		//Quick sort interface,allows us to call quicksort by simply passing the array
	    public void quickSort(int arr[]) {
	    	//calculate the array length
	    	int n = arr.length;
	    	//call quicksort
	    	quickSort(arr, 0, n-1);
	    }
	    
		/* This function takes last element as pivot,
	    places the pivot element at its correct
	    position in sorted array, and places all
	    smaller (smaller than pivot) to left of
	    pivot and all greater elements to right
	    of pivot */
		private int partition(int arr[], int low, int high){
		     int pivot = arr[high]; 
		     int i = (low-1); // index of smaller element
		     
		     for (int j=low; j<high; j++){
		    	 // If current element is smaller than or
		         // equal to pivot
		         if (arr[j] <= pivot){
		        	 i++;
		
		             // swap arr[i] and arr[j]
		             int temp = arr[i];
		             arr[i] = arr[j];
		             arr[j] = temp;
		             
		             //after a swap, repaint the panel so we can show the animation
		             repaint();
		             //pause the thread to slow down the animation
		             try {
		            	 Thread.sleep(THREAD_SLEEP);
		             } catch (InterruptedException e) {
						 e.printStackTrace();
		             }
		         }
		     }
		
		     // swap arr[i+1] and arr[high] (or pivot)
		     int temp = arr[i+1];
		     arr[i+1] = arr[high];
		     arr[high] = temp;
		     
		     repaint();
             //pause the thread to slow down the animation
             try {
            	 Thread.sleep(THREAD_SLEEP);
             } catch (InterruptedException e) {
				 e.printStackTrace();
             }
		
		     return i+1;
		 }
		
		
		 /* The main function that implements QuickSort()
		   arr[] --> Array to be sorted,
		   low  --> Starting index,
		   high  --> Ending index */
		 private  void quickSort(int arr[], int low, int high){
		     if (low < high){
		         /* pi is partitioning index, arr[pi] is 
		           now at right place */
		         int pi = partition(arr, low, high);
		
		         // Recursively sort elements before
		         // partition and after partition
		         quickSort(arr, low, pi-1);
		         quickSort(arr, pi+1, high);
		     }
		 }
		
	}
}
