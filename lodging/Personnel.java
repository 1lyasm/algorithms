package org.ilyasmustafazade;

public class Personnel implements IViewable {
    int id;
    String name;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Personnel(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public String toString() {
        return "Personnel " + "[id=" + Integer.toString(this.id) + ", name=" + this.name + "]";
    }
}
