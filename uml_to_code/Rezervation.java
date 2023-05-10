package uml_to_code;

public class Rezervation {

  private static int counter = 0;
  private int rezervationID;
  private Hotel hotel;
  private int roomNumber;
  private int day;

  public Rezervation(Hotel hotel, int roomNumber, int day) {
    this.roomNumber = roomNumber;
    this.day = day;
    this.hotel = hotel;
    rezervationID = 20230001 + counter;
    ++counter;
  }

  public static void setCounter(int counter) { Rezervation.counter = counter; }

  public static int getCounter() { return counter; }

  @Override
  public String toString() {
    return "Rezervation [rezervationID=" + rezervationID + ", hotel=" + hotel +
        ", roomNumber=" + roomNumber + ", day=" + day + "]\n\n";
  }

  public void setRezervationID(int rezervationID) {
    this.rezervationID = rezervationID;
  }

  public void setHotel(Hotel hotel) { this.hotel = hotel; }

  public void setRoomNumber(int roomNumber) { this.roomNumber = roomNumber; }

  public void setDay(int day) { this.day = day; }

  public int getRezervationID() { return rezervationID; }

  public Hotel getHotel() { return hotel; }

  public int getRoomNumber() { return roomNumber; }

  public int getDay() { return day; }

  void calculatePayment() {
    for (Room room : hotel.getRooms()) {
      if (room.getRoomNumber() == roomNumber) {
        System.out.printf("%d gunluk  odeme tutari: %f\n", day,
                          day * room.getPrice());
      }
    }
  }
}
