package com.company;

public class Vertex {
    private String label;

    public Vertex(String name) {
        this.setLabel(name);
    }
    public String getLabel() {
        return this.label;
    }
    public void setLabel(String name) {
        this.label = name;
    }
}
