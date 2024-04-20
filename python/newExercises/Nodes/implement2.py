class DoubleNode():        
    def __init__(self, value = 0, previous = None, next = None, CreateList = False):
        if(not CreateList):
            self.value = value
            self.previous = previous
            self.next = next
            if(previous is not None):
                self.previous.next = self
            if(next is not None):
                self.next.previous = self

        else:
            pass

    def AddBefore(self, x):
        if(x == None):
            self.previous = x
            return
        if(type(x) != DoubleNode):
            x = DoubleNode(x)
        if(self.previous == None):
                x.next = self
                self.previous = x
                return
        # there is already a linkednode at previous
        savePrev = self.previous
        savePrev.next = x
        x.previous = savePrev
        x.next = self
        self.previous = x
    
    def AddAfter(self, x):
        if(x == None):
            self.next = None
            return
        if(type(x) != DoubleNode):
            x = DoubleNode(x)
        if(self.next == None):
                x.previous = self
                self.next = x
                return
        # there is already a linkednode at previous
        saveNext = self.next
        saveNext.previous = x
        x.next = saveNext
        x.previous = self
        self.next = x

    def PrintNodes(self):
        current = self
        while(current.previous != None):
            current = current.previous
        print(f"None <--", end = "")
        
        while(current.next != None):
            if(current == self):
                print(f"[{current.value} (current)]<-->", end = "")
            else:
                print(f"[{current.value}]<-->", end = "")
            current = current.next
        
        print(f"[{current.value}", end = "")
        if(current == self):
            print(" (current)", end = "")
        print(f"]--> None")


class TwoWayNode:
    def __init__(self, value = 0, previous = None, next = None):
        self.value = value
        self.previous = previous
        self.next = next

    def print(self):
        print("hey")

class TwoWayList(TwoWayNode):
    def __init__(self, value = 0, previous = None, next = None):
        super().__init__(value, previous, next)

    #I just realized there is no point in this
    

'''
d1 = DoubleNode(2)
d2 = DoubleNode(6, previous = d1)
d3 = DoubleNode(33, previous = d2)
d2.PrintNodes()
'''
