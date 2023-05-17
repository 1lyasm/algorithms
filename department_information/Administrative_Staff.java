package department_information;
public class Administrative_Staff extends Staff {

  public Administrative_Staff(int staff_id, String name, String web) {
    this.staff_id = staff_id;
    this.name = name;
    this.web = web;
  }
  
  public void add_commission(Department department, Commission commission) {
    department.getCommissions().add(commission);
  }

  public void add_academic_staff(Department d, Academic_Staff staff1) {
    d.getAcademic_staffs().add(staff1);
  }

  public void add_staff_to_commission(Department d, int staff_id, String commission_name) {
    int com_id = 0;
    for (Commission c: d.getCommissions()) {
      if (c.getName().equals(commission_name)) {
        com_id = c.getCommission_id();
      }
    }
    for (Academic_Staff a: d.getAcademic_staffs()) {
      if (a.getStaff_id() == staff_id) {
        a.setCom_id(com_id);
      }
    }
  }

  public void print_commission_information(Department d) {
    for (Commission c : d.getCommissions()) {
      System.out.println("\t" + Integer.toString(c.getCommission_id()) + ". Commission: " + c.getName());
      boolean there_is_staff = false;
      for (Academic_Staff a: d.getAcademic_staffs()) {
        if (c.getCommission_id() == a.getCom_id()) {
          System.out.println("\t\t" + Integer.toString(c.getCommission_id()) + ". Academic Personal: " + a.getName());
          there_is_staff = true;
        }
      }
      if (there_is_staff == false) {
        System.out.println("\t\tThere is no one on this commission.");
      }
    }
  }

  public Academic_Staff get_academic_staff(Department d, int ind) {
    return d.getAcademic_staffs().get(ind);
  }

  public void get_academic_staffs(Department d) {
    for (Academic_Staff a : d.getAcademic_staffs()) {
      a.print_staff_information();
    }
  }

  public Commission get_commission(Department d, String name) {
    for (Commission c: d.getCommissions()) {
      if (c.getName().equals(name)) {
        return c;
      }
    }
    return null;
  }

  public String get_department_history(Department d) {
    return d.getHistory();
  }

  public String get_department_mission_and_vision(Department d) {
    return d.getMission_and_vision();
  }

  public String get_department_name(Department d) {
    return d.getName();
  }

  public void print_staff_information(Department d) {
    d.print_academic_staffs_information();
  }

  @Override
  public void print_staff_information() {   
    System.out.println("\tName: " + this.name + ", Mail: " + this.mail +
      ", Staff ID: " + this.staff_id + ", Web: " + this.web + "\n");
  }
}
