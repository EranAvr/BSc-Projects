package com.company;

public class HashTableData {
    private String key; // Hash Table key
    // Additional fields

    public HashTableData (String key1){
        setKey(key1);
    }
    public void setKey(String key1) {
        this.key = key1;
    }
    public String getKey(){
        return this.key;
    }
}
