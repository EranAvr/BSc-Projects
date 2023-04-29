package com.company;

public class HashTable {
    private static final int DEF_MAX_HASH_SIZE = 10; // Default maximum hash table size
    private SLinkedList <HashTableData> [] hashArray; // Array containing the lists of keys
    private int numOfElements;

    // Constructors and helper method setup
    public HashTable() throws Exception {
        this(DEF_MAX_HASH_SIZE);
    }
    public HashTable(int maxNumber) throws Exception {
        if (maxNumber <= 0){
            throw new Exception("Hash table size must be greater than 0");
        }
        hashArray = new SLinkedList [maxNumber];
        for (int i=0 ; i<hashArray.length ; i++){
            hashArray[i] = new SLinkedList<>();
        }
        this.numOfElements = 0;
    }

    // HashFunctions
    int HashFunction(int key){
        if (key <= 0){
            return 1;
        }
        return key % hashArray.length;
    }
    int HashFunction(String key){
        int sum = 0;
        for (int i=0 ; i<key.length() ; i++){
            sum += key.charAt(i);
        }
        return this.HashFunction(sum);
    }

    // Hash manipulation methods
    public boolean retrieve(HashTableData searchElem) {
        if (this.isEmpty()){
            return false;
        }
        int index = this.HashFunction(searchElem.getKey());
        hashArray[index].gotoBeginning();
        do {
            if (    hashArray[index].getCursor() != null &&
                    hashArray[index].getCursor().getElement().getKey().equals(searchElem.getKey())  ){
                return true;
            }
        } while (hashArray[index].gotoNext());
        return false;
    }
    public boolean insert(HashTableData newElem) {
        if (this.isFull()){
            return false;
        }
        int index = this.HashFunction(newElem.getKey());
        this.hashArray[index].insert(new SNode(newElem, null));
        this.numOfElements++;
        return true;
    }
    public boolean remove(HashTableData remElem) {
        if (this.isEmpty()){
            return false;
        }
        int index = this.HashFunction(remElem.getKey());
        hashArray[index].gotoBeginning();
        do {
            if ( hashArray[index].getCursor().getElement().getKey().equals(remElem.getKey()) ){
                hashArray[index].remove();
                this.numOfElements--;
                return true;
            }
        } while (hashArray[index].gotoNext());
        return false;
    }
    public void clear(){
        for (int i=0 ; i<hashArray.length ; i++){
            hashArray[i].clear();
        }
        this.numOfElements = 0;
    }

    // Hash status methods
    public boolean isEmpty(){
        return this.numOfElements==0;
    }
    public boolean isFull(){
        for (int i=0 ; i<hashArray.length ; i++){
            if (hashArray[i].isEmpty()){
                return false;
            }
        }
        return true;
    }

    // Output the hash structure
    public String toString(){
        String res = "";
        for (int i=0 ; i<hashArray.length ; i++){
            res += "["+i+"]";
            hashArray[i].gotoBeginning();
            do {
                if (hashArray[i].getCursor()==null){
                    break;
                }
                else {
                    res += " --> ";
                }
                res += hashArray[i].getCursor().getElement().getKey();
            } while (hashArray[i].gotoNext());
            res += "\n";
        }
        return res;
    }
}
