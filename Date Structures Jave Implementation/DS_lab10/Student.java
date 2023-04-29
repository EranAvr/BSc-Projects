package com.company;

public class Student extends HashTableData {
    private int id, age;
    private String fname, lname;
    private double avg;

    public Student(int id, String f_name, String l_name, int age, double avg) {
        //  You can define any field as key by sending
        //  it to the super's constructor
        super(l_name);
        //  Initializing fields
        this.id = id;
        this.fname = f_name;
        this.lname = l_name;
        this.age = age;
        this.avg = avg;
    }

    @Override
    public String toString() {
        return "Student{" +
                "KEY=" + getKey() + " | " +
                "id=" + id +
                ", age=" + age +
                ", fname='" + fname + '\'' +
                ", lname='" + lname + '\'' +
                ", avg=" + avg +
                '}';
    }
}
