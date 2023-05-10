package uml_to_code;

public class Room {

  private int roomNumber;
  private String roomType;
  private double price;
  private boolean isAvailable;

  public Room(int roomNumber, String roomType, double price) {
    this.roomNumber = roomNumber;
    this.roomType = roomType;
    this.price = price;
    isAvailable = true;
  }

  public void setRoomNumber(int roomNumber) {
    this.roomNumber = roomNumber;
  }

  public String toString() {
    return "Room [roomNumber=" + roomNumber + ", roomType=" + roomType + ", price=" + price + ", isAvailable="
        + isAvailable + "]";
  }

  public void setRoomType(String roomType) {
    this.roomType = roomType;
  }
  public void setPrice(double price) {
    this.price = price;
  }
  public void setAvailable(boolean isAvailable) {
    this.isAvailable = isAvailable;
  }
  public int getRoomNumber() {
    return roomNumber;
  }
  public String getRoomType() {
    return roomType;
  }
  public double getPrice() {
    return price;
  }
  public boolean isAvailable() {
    return isAvailable;
  }
}
