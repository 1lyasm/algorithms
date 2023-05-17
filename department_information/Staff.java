package department_information;
public abstract class Staff {
  String mail;
  String name;
  int staff_id;
  String web;

  // public Staff(int staff_id, String name, String web) {
  //   this.staff_id = staff_id;
  //   this.name = name;
  //   this.web = web;
  // }

  // public Staff(int staff_id, String name, String web, String mail) {
  //   this.staff_id = staff_id;
  //   this.name = name;
  //   this.web = web;
  //   this.mail = mail;
  // }

  public String getMail() {
    return mail;
  }
  public String getName() {
    return name;
  }
  public int getStaff_id() {
    return staff_id;
  }
  public void setMail(String mail) {
    this.mail = mail;
  }
  public void setName(String name) {
    this.name = name;
  }
  public void setStaff_id(int staff_id) {
    this.staff_id = staff_id;
  }
  public void setWeb(String web) {
    this.web = web;
  }
  public String getWeb() {
    return web;
  }

  abstract public void print_staff_information();
}
