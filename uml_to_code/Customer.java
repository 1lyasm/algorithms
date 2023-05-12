package uml_to_code;

import java.util.ArrayList;

public class Customer {
  private String name;
  private int identityID;
  private ArrayList<Rezervation> rezervations = new ArrayList<Rezervation>();

  public Customer(String name, int identityID) {
    this.name = name;
    this.identityID = identityID;
  }

  public String getName() {
    return name;
  }

  public int getIdentityID() {
    return identityID;
  }

  public void setName(String name) {
    this.name = name;
  }

  public void setIdentityID(int identityID) {
    this.identityID = identityID;
  }

  public void setRezervations(ArrayList<Rezervation> rezervations) {
    this.rezervations = rezervations;
  }

  public ArrayList<Rezervation> getRezervations() {
    return rezervations;
  }

  public void listCustomerRezervations() {
    System.out.println(rezervations);
  }

  public void getInvoice(int rezervationID) {
    for (Rezervation rezervation : rezervations) {
      if (rezervation.getRezervationID() == rezervationID) {
        rezervation.calculatePayment();
      }
    }
  }

  public void makeRezervation(Hotel hotel, String roomType, int day) {
    ArrayList<Room> rooms = hotel.getRooms();
    for (int i = 0; i < rooms.size(); ++i) {
      Room room = rooms.get(i);
      if (room.isAvailable() && roomType.equals(room.getRoomType())) {
        room.setAvailable(false);
        Rezervation newRezervation = new Rezervation(hotel, room.getRoomNumber(), day);
        rezervations.add(newRezervation);
        return;
      }
    }
    System.out.println("Sectiginiz oda tipi icin musaitlik bulunamadi.");
  }
}
