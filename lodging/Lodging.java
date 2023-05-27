package org.ilyasmustafazade;

import java.util.*;

public class Lodging {
  int counter;
  HashMap<Personnel, Apartment> hm = new HashMap<Personnel, Apartment>();
  List<Personnel> p_list;
  List<Apartment> a_list;

  public int getCounter() {
    return counter;
  }

  public void setCounter(int counter) {
    this.counter = counter;
  }

  public HashMap<Personnel, Apartment> getHm() {
    return hm;
  }

  public void setHm(HashMap<Personnel, Apartment> hm) {
    this.hm = hm;
  }

  public List<Personnel> getP_list() {
    return p_list;
  }

  public void setP_list(List<Personnel> p_list) {
    this.p_list = p_list;
  }

  public List<Apartment> getA_list() {
    return a_list;
  }

  public void setA_list(List<Apartment> a_list) {
    this.a_list = a_list;
  }

  public void placement(ArrayList<Personnel> p_list, LinkedList<Apartment> a_list) {
    this.p_list = p_list;
    this.a_list = a_list;
    int big_len = Math.max(a_list.size(), p_list.size());
    for (int i = 0; i < big_len; ++i) {
      Personnel p = null;
      Apartment a = null;
      if (i < p_list.size())
        p = p_list.get(i);
      if (i < a_list.size())
        a = a_list.get(i);
      hm.put(p, a);
    }
  }

  public void mapPrint() {
    if (this.hm.isEmpty()) {
      System.out.println("No one living in the lodging");
      return;
    }
    for (Map.Entry<Personnel, Apartment> entry : hm.entrySet()) {
      Personnel p = entry.getKey();
      Apartment a = entry.getValue();
      if (p != null && a != null) {
        System.out.println("P_Id:" + p.getId() + " personel lives in -> Apartment " + a.getId());
      }
    }
  }

  public void returnApartment(Personnel personnel) {
    Personnel waiting_personnel = null, existing_personnel = null;
    if (!this.hm.containsKey(personnel)) {
      System.out.println(
          personnel.getId() + "," + personnel.getName() + " has already returned the daire.");
    }
    boolean found = false;
    for (Map.Entry<Personnel, Apartment> entry : hm.entrySet()) {
      if (!found) {
        Personnel p = entry.getKey();
        Apartment a = entry.getValue();
        if (personnel.getId() == p.getId()) {
          if (a == null) {
            System.out.println(p.getId() + "," + p.getName() + " has already returned the daire.");
          } else {
            Personnel waiting_p = null;
            for (Map.Entry<Personnel, Apartment> entry_in : hm.entrySet()) {
              Personnel p_in = entry_in.getKey();
              Apartment a_in = entry_in.getValue();
              if (p_in != null && a_in == null) {
                waiting_p = p_in;
              }
            }
            if (waiting_p != null) {
              waiting_personnel = waiting_p;
              existing_personnel = p;
              System.out.println("P_Id:" + p.getId() + " personel returned the Aprtmnt_Id: "
                  + a.getId() + " and new personnel was placed in it.");
              found = true;
            } else {
              existing_personnel = p;
              System.out.println("P_Id:" + a.getId()
                  + " has been  returned, however, no placement was made because there was no other staff waiting in line.");
              found = true;
            }
          }
        }
      }
    }
    if (existing_personnel != null && waiting_personnel != null) {
      Apartment a = hm.get(existing_personnel);
      hm.remove(existing_personnel);
      hm.remove(waiting_personnel);
      hm.put(waiting_personnel, a);
    } else if (waiting_personnel == null && existing_personnel != null) {
      hm.remove(existing_personnel);
    }
  }

  public void newApartment() throws ApartmentException {
    this.placement((ArrayList<Personnel>) this.p_list, (LinkedList<Apartment>) this.a_list);
    Scanner scanner = new Scanner(System.in);
    System.out.println("Enter apartment id: ");
    int id = scanner.nextInt();
    System.out.println("Enter type: ");
    String type = scanner.next();
    scanner.close();
    for (Apartment a : this.a_list) {
      if (a.getId() == id) {
        throw new ApartmentException("Lodging has this apartment!");
      }
    }
    System.out.println("New apartment added.");
    Apartment new_a = new Apartment(id, type);
    a_list.add(new_a);
    Personnel waiting_p = null;
    for (Map.Entry<Personnel, Apartment> entry : hm.entrySet()) {
      Personnel p = entry.getKey();
      Apartment a = entry.getValue();
      if (p != null && a == null) {
        waiting_p = p;
      }
    }
    if (waiting_p == null) {
      System.out.println(
          "There is no one waiting for apartment, apartment id: " + id + ", type: " + type);
    } else {
      this.placement(waiting_p, new_a);
    }
  }

  private void placement(Personnel waiting_p, Apartment a) {
    this.hm.replace(waiting_p, null, a);
    System.out.println("P_Id:" + waiting_p.getId() + " was placed in Aprtmnt_Id: " + a.getId());
    System.out.println(
        "P_Id:" + waiting_p.getId() + " personel lives in -> Apartment " + a.getId());
  }
}
