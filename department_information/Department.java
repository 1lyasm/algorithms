package department_information;

import java.util.ArrayList;

public class Department {
  public ArrayList<Academic_Staff> getAcademic_staffs() {
    return academic_staffs;
  }

  public void setAcademic_staffs(ArrayList<Academic_Staff> academic_staffs) {
    this.academic_staffs = academic_staffs;
  }

  public ArrayList<Commission> getCommissions() {
    return commissions;
  }

  public void setCommissions(ArrayList<Commission> commissions) {
    this.commissions = commissions;
  }

  public String getHistory() {
    return history;
  }

  public void setHistory(String history) {
    this.history = history;
  }

  public String getMission_and_vision() {
    return mission_and_vision;
  }

  public void setMission_and_vision(String mission_and_vision) {
    this.mission_and_vision = mission_and_vision;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  ArrayList<Academic_Staff> academic_staffs;
  ArrayList<Commission> commissions;
  String history;
  String mission_and_vision;
  String name;

  public Department(String department_name, String department_history, String mission_and_vision) {
    this.name = department_name;
    this.history = department_history;
    this.mission_and_vision = mission_and_vision;
    this.commissions = new ArrayList<Commission>();
    this.academic_staffs = new ArrayList<Academic_Staff>();
  }

  public void print_academic_staffs_information() {
    for (Academic_Staff a : this.academic_staffs) {
      System.out.print(a.getOffice() + " ");
    }
  }
}
