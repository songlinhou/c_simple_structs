# c_simple_structs
Lightweight alternative of C++ std in C with class.method() style!

## Quick Example

```
//working with integers.
struct SPArrayList* intList = SPArrayListCreator.newArrayList(INT); // specify the stored

intList->add(intList,1);
intList->add(intList,2);
intList->add(intList,3);
intList->add(intList,4);

for(int i=0; i < intList->count; i++){
    int value = (int)intList->get(intList, i);
    printf("\n value at index %d = %d\n",i,value);
}
```


```
//working with char*.
struct SPArrayList* strList = SPArrayListCreator.newArrayList(CHAR_ARRAY);
strList->add(strList,"this is first");
strList->add(strList,"this is second");
strList->add(strList,"this is third");
strList->add(strList,"this is fourth");

for(int i=0; i < strList->count; i++){
   char* value = (char *)strList->get(strList, i);
   printf("\n value at index %d = %s\n",i,value);
}

```
## Available Structs

### **SPArrayList**
#### constructor
`SPArrayList* SPArrayListCreator.newArrayList(SPType)`
create a new arraylist of type SPType and returns its address.

#### public attributes:
`int count`
number of elements in this list.

#### public methods:
`void add(SPArrayList* self, void* data)  `
add an element in the end of array. 

`void* get(SPArrayList* self, int index) 
`
return an element at the index position.

-------



### **SPHashMap**
#### constructor
`struct SPHashMap* SPHashMapCreator.newHashMap(SPType);`
create a new arraylist of type SPType and returns its address. Continuous memory is used in this structure.

#### public attributes:
`None`
#### public methods:
`void put(struct SPHashMap* self, long key, long value)`
put a key-value pair into hashmap.

`long get(struct SPHashMap* self, long key)`
get the value based on the key.

`int hasKey(struct SPHashMap* self, long key)`
check if a key exists in the map.

`SPArrayList* keys(struct SPHashMap* self)`
return all keys of a hashmap as a arraylist.

