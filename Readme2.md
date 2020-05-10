# Linked List

linked_list.chl

```
record Node {
  const value: int;
  mut next: Node?;
}

record List {
  const hd: Node?;
}

fn add(const l: List, const val: int){
  with l.head as cur {
    loop {
      with cur.next as next {
        cur = next;
        continue;
      }
      break;
    }
    cur.next = Node { value = val };
  }
}
```
