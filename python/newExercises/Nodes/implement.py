#/usr/bin/env python3

import string

def Polindrom(sentence):
    str_chars = string.ascii_lowercase + string.ascii_uppercase + '0123456789'
    new_str = "".join([char for char in sentence if char in str_chars])
    for i in range(0, len(new_str) // 2, 1): 
        if(new_str[i] != new_str[len(new_str) - 1 - i]):
            return False
    return True
    
def PolindromEasy(sentence):
    return sentence == sentence[::-1]
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
class Node:
    def __init__(self, value = 0, next = None, CreateLoop = False):
        if(CreateLoop == False):
            self.value = value
            self.next = next
        else:
            NodeCreated = False
            print("Please enter a number for creating a node, enter anything else to quit: ")
            while (1):
                num = input()
                if(num.isnumeric()):
                    num = int(num)
                    if(NodeCreated == False):
                        self.value = num
                        self.next = None
                        current = self
                        NodeCreated = True
                    else:
                        tmp = Node(num)
                        current.next = tmp
                        current = tmp
                else:
                    if(NodeCreated == False):
                        print("You have to create at least 1 Node!")
                    else:
                        return
                    
    def SetNext(self, next):
        self.next = next
    def SetValue(self, value):
        self.value = value
    def GetNext(self):
        return self.next
        
    def PrintNodes(self):
        current = self
        while(current.next != None):
            print(f"{current.value} --> ", end = "")
            current = current.next
        print(f"{current.value} --> None")
        
    def ReverseNodes(self):
        currentNode = self
        setTo = None
        while(currentNode != None):
            nextNode = currentNode.next
            currentNode.next = setTo
            setTo = currentNode
            currentNode = nextNode
        return setTo
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
class DoubleNode():
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
        
    def __init__(self, value = 0, previous = None, next = None, CreateList = False):
        if(not CreateList):
            self.previous = None
            self.next = None
            self.value = value
            if(previous is not None):
                self.AddBefore(previous)
            if(next is not None):
                self.AddAfter(next)
        else:
            pass
        
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
        print(f"]--> None", end = "")

if(__name__ == "__main__"):
    '''
    d1 = DoubleNode(5)
    d2 = DoubleNode(2, previous = d1, next = None)
    d3 = DoubleNode(10)
    d2.AddBefore(d3)
    d2.PrintNodes()
    '''
    
    '''
    x1 = Node(1)
    x2 = Node(2, x1)
    x3 = Node(3, x2)
    
    x3.PrintNodes()
    x4 = x3.ReverseNodes()
    x4.PrintNodes()
    
    x5 = Node(CreateLoop = True)
    x5.PrintNodes()
    '''
    
    '''
    print(PolindromEasy("abcdba"))
    print(Polindrom("abcdba"))
    
    print(PolindromEasy("abcba"))
    print(Polindrom("abcba"))
    
    print(PolindromEasy("aa"))
    print(Polindrom("aa"))
    '''