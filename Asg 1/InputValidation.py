# BY ANKITA KAPOOR
# Student ID: 20811694
import re

error_message=''
lst = []
class InputValidation(object):
    def inputValidation(self,input):
        input = input.strip()
        if input[0] == 'a'or input[0] == 'c' or input[0] == 'r' or input[0] == 'g':
            if input[0] == 'a':
                s=""
                count1 = count2 = count3 =0
                if input[1:].strip()[0] == "\"":
                    pass
                else:
                    self.setErrorMessage('Error: Invalid Input character found between the command and Street Name')
                    return False
                if len(input.split('\"')) == 3:
                    if input.split('\"')[1] == "" or input.split('\"')[1] == " ":
                        self.setErrorMessage('Error: Given Street Name is invalid')
                        return False
                for i in range(len(input)):
                    if input[i] == "\"":
                        j = i
                for k in range(j, len(input)):
                    if input[k] == "(":
                        s = input[j+1:k]
                        break
                for i in range(len(s)):
                    if s[i] == " " or s[i] == "":
                        pass
                    else:
                        self.setErrorMessage('Error: Input string between Street Name and coord is invalid')
                        return False
                for i in range(len(input)):
                    if input[i] == "(":
                        count1+=1
                    elif input[i] == ")":
                        count2+=1
                    elif input[i] == ",":
                        count3+=1
                if count1 == count2 == count3:
                    pass
                else:
                    self.setErrorMessage('Error: Invalid Input! There is no match between Braces and Commas.')
                    return False
                if count1>=2:
                    pass
                else:
                    self.setErrorMessage('Error: Invalid! Please provide at least 2 coordinates')
                    return False
        else:
            error_message ='Error: Input should only begin with a,c,r,g'
            self.setErrorMessage(error_message)
            return False

        if input[0] == 'a' or input[0] == 'c' or input[0] == 'r':
            if input[1] == " ":
                pass
            else:
                self.setErrorMessage('Error: The second character should be a space.')
                return False
        if input[0] == 'a' or input[0] == 'c':
            for m in range(len(input)):
                if input[m] == '(':
                    if input[m-1] == " ":
                        break
                    else:
                        self.setErrorMessage('Error: Space required after the Street Name.')
                        return False
            a = input.find('(')
            inputList = input.split("(")
            for i in range(len(inputList)-1):
                if "," in inputList[i]:
                    for j in range(i+1,len(inputList)):
                        p1 = inputList[i].strip()[:-1].strip().split(',')
                        x1 = p1[0]
                        y1 = p1[1]
                        p2 = inputList[j].strip()[:-1].strip().split(',')
                        x2 = p2[0]
                        y2 = p2[1]
                        if x1 == x2 and y1 == y2:
                            self.setErrorMessage('Error: The Coordinates of a street cannot be same.')
                            return False
            input = input[a+1:len(input)-1]
            regex = re.compile('[a-z]|[A-Z]')
            if len(regex.findall(input))>0:
                self.setErrorMessage('Error: Invalid Input!')
                return False
            else:
                pass

    def setErrorMessage(self,message):
        print message

    def removeSpaceCoord(self,input):
        s=""
        j=0
        i=0
        regex = re.compile('[a-z]|[A-Z]')
        while i < (len(input)):
            if input[i] == "(":
                j=i
                while input[j] !=")":
                    if input[j] == " ":
                        i+=1
                        j+=1
                    else:
                        if len(regex.findall(input[j]))>0:
                            self.setErrorMessage("Error: Coordinates cannot be [a-z][A-Z]")
                            return False
                        else:
                            s = s+input[j]
                            j+=1
                            i+=1
                s = s+input[j]
                if j != len(input)-1:
                    if input[j+1] != " ":
                        s = s + " "
            else:
                s=s+input[i]
            i+=1
        return s

    def validateAddStreetCase(self, streetName, streetDictionary):
        st = streetDictionary.keys()
        flag = False
        for i in range(len(st)):
            if streetName.lower() == st[i].lower():
                flag = True
            else:
                flag = False
                break
        if flag is True:
            self.setErrorMessage("Error: You cannot add a already existing street.")
            return False
        else:
            return True

    def validateChangeStreetCase(self, streetName, streetDictionary, input):
        st = streetDictionary.keys()
        count=0
        flag = False
        for i in range(len(input)):
            if input[i] == "(":
                count+=1
        for j in range(len(st)):
            if streetName.lower() != st[j].lower() or count <2:
                flag = True
            else:
                flag = False
                break
        if flag is True:
            self.setErrorMessage("Error: Either the street does not exist or the points cannot be less than 2.")
            return False
        else:
            return True

    def validateRemoveStreetCase(self, streetName, streetDictionary, input):
        st = streetDictionary.keys()
        flag = False
        elements = input.strip().split("\"")
        for i in range(len(st)):
            if streetName.lower() != st[i].lower() or elements[-1] != '':
                flag = True
            else:
                flag = False
                break
        if flag is True:
            self.setErrorMessage("Error: The street does not exist or invalid input")
            return False
        return True

    def validateGenerateGraph(self, streetDictionary, input):
        st = streetDictionary.keys()
        if len(input.strip()) == 1:
            return True
        else:
            self.setErrorMessage("Error: Invalid Input! ")
            return False

