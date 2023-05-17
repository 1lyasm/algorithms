package department_information;

import java.util.ArrayList;

public class Academic_Staff extends Staff {

  int com_id;
  public int getCom_id() {
    return com_id;
  }

  public void setCom_id(int com_id) {
    this.com_id = com_id;
  }

  public String getOffice() {
    return office;
  }

  public void setOffice(String office) {
    this.office = office;
  }

  public ArrayList<String> getResearch_areas() {
    return research_areas;
  }

  public void setResearch_areas(ArrayList<String> research_areas) {
    this.research_areas = research_areas;
  }

  String office;
  ArrayList<String> research_areas;
  
  public Academic_Staff(int staff_id, String name, String web, String mail, String office) {
    this.staff_id = staff_id;
    this.name = name;
    this.web = web;
    this.mail = mail;
    this.office = office;
    this.research_areas = new ArrayList<String>();
  }

  public Academic_Staff(int staff_id, String name, String web) {
    this.staff_id = staff_id;
    this.name = name;
    this.web = web;
    this.research_areas = new ArrayList<String>();
  }

  public void add_research(String area) {
    this.research_areas.add(area);
  }

  public void delete_research(int i) {
    this.research_areas.remove(i);
  }

  public void delete_research(String string) {
    this.research_areas.remove(string);
  }

  @Override
  public void print_staff_information() {
      System.out.println("Name: " + this.name + ", Mail: " + this.mail +
        ", Staff_id: " + this.staff_id + ", Web: " + this.web + ", Com. ID: " + this.com_id +
          ", Office: " + this.office + "\n" + this.name + " Research Areas: ");
      for (String s: this.research_areas) {
        System.out.println(s + " ");
      }
      System.out.println("\n");
  }

  public ArrayList<String> get_research_areas() {
    return this.research_areas;
  }

  public String get_office() {
    return this.office;
  }
}
