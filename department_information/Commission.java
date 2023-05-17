package department_information;

public class Commission {

  public int getCommission_id() {
    return commission_id;
  }

  public void setCommission_id(int commission_id) {
    this.commission_id = commission_id;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  int commission_id;
  String name;

  public Commission(int commission_id, String name) {
    this.commission_id = commission_id;
    this.name = name;
  }
}
