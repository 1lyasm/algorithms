// javac -d uml_to_code *.java
// java -cp uml_to_code uml_to_code.Main


package uml_to_code;

import java.util.ArrayList;
import java.util.Arrays;

public class Main {
	
	public static void main(String[] args) {
		
		Hotel h1 = new Hotel("London Hotel", "London, UK", "0044201491866");
		Hotel h2 = new Hotel("Istanbul Hotel", "Istanbul, Turkey", "009212432121");

		ArrayList<Room> rooms = new ArrayList<Room>();
		rooms.add(new Room(101, "standart",100));
		rooms.add(new Room(201, "family",200));
		rooms.add(new Room(301,"suit",400));
		rooms.add(new Room(302,"suit",400));
		h1.setRooms(rooms);
		h2.setRooms(rooms);
		
		Customer c1 = new Customer("Jane Austen", 1112334455);
		
		c1.makeRezervation(h1, "suit", 3);
		c1.makeRezervation(h2, "family", 5);
		c1.makeRezervation(h1, "suit", 4);
		
		c1.listCustomerRezervations();  
		
		System.out.println("************************************************");
		c1.getInvoice(20230002);     //verilen rezervasyon numarasina ait odeme bilgileri listelenir.
		
		System.out.println("************************************************");
		Customer c2 = new Customer("Agatha Christie", 1133557799);
		c2.makeRezervation(h2, "family", 4);
	}
}
