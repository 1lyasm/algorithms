package org.ilyasmustafazade;

public class Apartment implements IViewable {
    int id;
    String type;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Apartment(int id, String type) {
        this.id = id;
        this.type = type;
    }

    public String toString() {
        return "Apartment " + "[id=" + Integer.toString(this.id) + ", type=" + this.type + "]";
    }
}
