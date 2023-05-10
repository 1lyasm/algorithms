package uml_to_code;

import java.util.ArrayList;

public class Hotel {
  private String hotelName;
  private String address;
  private String telephone;
  private ArrayList<Room> rooms = new ArrayList<Room>();
  

  public void setRooms(ArrayList<Room> rooms) {
    this.rooms = rooms;
  }

  public ArrayList<Room> getRooms() {
    return rooms;
  }

  public Hotel(String hotelName, String address, String telephone) {
    this.hotelName = hotelName;
    this.address = address;
    this.telephone = telephone;
  }

  public String getHotelName() {
    return hotelName;
  }

  public String getAddress() {
    return address;
  }

  public String getTelephone() {
    return telephone;
  }

  public void setHotelName(String hotelName) {
    this.hotelName = hotelName;
  }

  public void setAddress(String address) {
    this.address = address;
  }

  public void setTelephone(String telephone) {
    this.telephone = telephone;
  }

  @Override
  public String toString() {
    return "Hotel [hotelName=" + hotelName + "]";
  }
}
