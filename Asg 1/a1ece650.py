# BY ANKITA KAPOOR
# Student ID: 20811694
import math
from InputValidation import InputValidation

# MY CODE GOES HERE
vertexDictionary = {}
edgeDictionary = {}
count = 1
flag = False

class Graph():
    def main(self):
        streetDictionary = {}
        while True:
            input = raw_input()
            try:
                if input is not "":
                    input = input.strip()
                    validation = InputValidation()
                    if validation.inputValidation(input) is False:
                        pass
                    else:
                        if input[0] == "a" or input[0] == "A":
                            if validation.validateAddStreetCase(self.getStreetName(input), streetDictionary) is not False:
                                input = validation.removeSpaceCoord(input)
                                if input is not False:
                                    streetDictionary.update(
                                        {self.getStreetName(input): self.getStreetPos(input)})
                        elif input[0] == "c" or input[0] == "C":
                            if validation.validateChangeStreetCase(self.getStreetName(input), streetDictionary,
                                                           input) is not False:
                                del streetDictionary[self.getStreetName(input)]
                                input = validation.removeSpaceCoord(input)
                                if input is not False:
                                    streetDictionary.update(
                                        {self.getStreetName(input): self.getStreetPos(input)})
                        elif input[0] == "r" or input[0] == "R":
                            if validation.validateRemoveStreetCase(self.getStreetName(input), streetDictionary,
                                                           input) is not False:
                                del streetDictionary[self.getStreetName(input)]
                        elif input[0] == "g" or input[0] == "G":
                            if validation.validateGenerateGraph(streetDictionary, input) is not False:
                                vertexEdge = self.findVertex(streetDictionary)
                                vertex = vertexEdge[0]
                                edgeDic = vertexEdge[1]
                                verticesDic = self.setVertex(vertex)
                                self.printVertex(verticesDic)
                                edgeList = self.setEdges(edgeDic, verticesDic)
                                edgeList = list(set(edgeList))
                                edgeList = self.removeDuplicateEdgeList(edgeList)
                                self.printEdges(edgeList)
                else:
                    print "Error: You need to enter an input command!"
                    break
            except:
                print "Error: Invalid Input!"

    def getStreetName(self, input):
        street_name = []
        for i in range(len(input)):
            if input[i] == "\"":
                street_name.append(i)
        streetName = input[street_name[0] + 1:street_name[1]]
        streetName = streetName.lower()
        return streetName

    def getStreetPos(self, input):
        coord = []
        for i in range(len(input)):
            if input[i] == "(":
                coord = input[i:].split(" ")
                return coord

    def getFloatStr(self, point):
        s = ""
        x = float(point.split(",")[0][1:])
        y = float(point.split(",")[1][:-1])
        s = "(" + str(x) + ", " + str(y) + ")"
        return s

    def findVertex(self, streetDictionary):
        global edgeDictionary
        edgeDictionary.clear()
        streetName = streetDictionary.keys()
        vertexList = []
        for i in range(len(streetDictionary) - 1):
            coordCompTo = streetDictionary[streetName[i]]
            for j in range(len(coordCompTo) - 1):
                p11 = coordCompTo[j]
                p12 = coordCompTo[j + 1]
                for k in range(i + 1, len(streetDictionary)):
                    coordCompWith = streetDictionary[streetName[k]]
                    for l in range(len(coordCompWith) - 1):
                        p21 = coordCompWith[l]
                        p22 = coordCompWith[l + 1]
                        intersectionPt = self.getLines(p11, p12, p21, p22)
                        if intersectionPt is not False and intersectionPt != 'm,n':
                            vertexList.append(str(intersectionPt))
                            vertexList.append(self.getFloatStr(p11))
                            vertexList.append(self.getFloatStr(p12))
                            vertexList.append(self.getFloatStr(p21))
                            vertexList.append(self.getFloatStr(p22))
                            edgeDictionary = self.setEdgeDic(str(intersectionPt), self.getFloatStr(p11),
                                                        self.getFloatStr(p12), self.getFloatStr(p21),
                                                        self.getFloatStr(p22), streetName[i], streetName[k])
                        elif intersectionPt == 'm,n':
                            if flag is False:
                                vertexList.append(self.getFloatStr(p11))
                                vertexList.append(self.getFloatStr(p12))
                                vertexList.append(self.getFloatStr(p21))
                                vertexList.append(self.getFloatStr(p22))
                                edgeDictionary = self.setEdgeDicUpated(self.getFloatStr(p21),
                                                               self.getFloatStr(p22),
                                                               self.getFloatStr(p11),
                                                               self.getFloatStr(p12), streetName[i], flag)
                            elif flag is True:
                                vertexList.append(self.getFloatStr(p11))
                                vertexList.append(self.getFloatStr(p12))
                                vertexList.append(self.getFloatStr(p21))
                                vertexList.append(self.getFloatStr(p22))
                                edgeDictionary = self.setEdgeDicUpated(self.getFloatStr(p11),
                                                               self.getFloatStr(p12),
                                                               self.getFloatStr(p21),
                                                               self.getFloatStr(p22), streetName[k], flag)
        edgeDictionary = self.removeDuplicate(edgeDictionary)
        edgeDictionary = self.validateInter(edgeDictionary)
        vertexEdge = [vertexList, edgeDictionary]
        return vertexEdge

    def getLines(self, line1pt1, line1pt2, line2pt1, line2pt2):
        x1 = float(line1pt1.split(",")[0][1:])
        x2 = float(line1pt2.split(",")[0][1:])
        x3 = float(line2pt1.split(",")[0][1:])
        x4 = float(line2pt2.split(",")[0][1:])
        y1 = float(line1pt1.split(",")[1][:-1])
        y2 = float(line1pt2.split(",")[1][:-1])
        y3 = float(line2pt1.split(",")[1][:-1])
        y4 = float(line2pt2.split(",")[1][:-1])
        l1 = ((x1, y1), (x2, y2))
        l2 = ((x3, y3), (x4, y4))
        intersectionPoint = self.getIntersectionPt(l1, l2)
        return intersectionPoint

    def getIntersectionPt(self, l1, l2):
        xdiff = (l1[0][0] - l1[1][0], l2[0][0] - l2[1][0])
        ydiff = (l1[0][1] - l1[1][1], l2[0][1] - l2[1][1])
        global flag

        def det(m, n):
            return m[0] * n[1] - m[1] * n[0]

        div = float(det(xdiff, ydiff))
        if div != 0:
            d = (det(*l1), det(*l2))
            x = round((det(d, xdiff) / div), 2)
            y = round((det(d, ydiff) / div), 2)
            if x == -0.0:
                x = 0.0
            if y == -0.0:
                y = 0.0
            d11 = float(math.sqrt((l1[0][0] - x) ** 2 + (l1[0][1] - y) ** 2))
            d12 = float(math.sqrt((l1[1][0] - x) ** 2 + (l1[1][1] - y) ** 2))
            dist1 = float(math.sqrt((l1[0][0] - l1[1][0]) ** 2 + (l1[0][1] - l1[1][1]) ** 2))
            d21 = float(math.sqrt((l2[0][0] - x) ** 2 + (l2[0][1] - y) ** 2))
            d22 = float(math.sqrt((l2[1][0] - x) ** 2 + (l2[1][1] - y) ** 2))
            dist2 = float(math.sqrt((l2[0][0] - l2[1][0]) ** 2 + (l2[0][1] - l2[1][1]) ** 2))
            distStr1 = d11 + d12
            distStr2 = d21 + d22
            if abs(distStr1 - dist1) < 0.001 and abs(distStr2 - dist2) < 0.001:
                return x, y
            else:
                return False
        else:
            dist1 = float(math.sqrt((l1[0][0] - l1[1][0]) ** 2 + (l1[0][1] - l1[1][1]) ** 2))
            dist2 = float(math.sqrt((l2[0][0] - l2[1][0]) ** 2 + (l2[0][1] - l2[1][1]) ** 2))
            if dist1 > dist2:
                flag = False
                distance = dist1
                d11 = float(math.sqrt((l1[0][0] - l2[0][0]) ** 2 + (l1[0][1] - l2[0][1]) ** 2))
                d12 = float(math.sqrt((l1[1][0] - l2[1][0]) ** 2 + (l1[1][1] - l2[1][1]) ** 2))
                distStr1 = d11 + d12 + dist2
                if abs(distStr1 - distance) < 0.001:
                    return 'm,n'
                else:
                    return False
            elif dist2 > dist1:
                flag = True
                distance = dist2
                d11 = float(math.sqrt((l2[0][0] - l1[0][0]) ** 2 + (l2[0][1] - l1[0][1]) ** 2))
                d12 = float(math.sqrt((l2[1][0] - l1[1][0]) ** 2 + (l2[1][1] - l1[1][1]) ** 2))
                distStr1 = d11 + d12 + dist1
                if abs(distStr1 - distance) < 0.001:
                    return 'm,n'
                else:
                    return False
            return False

    def setVertex(self, verticesList):
        global count
        global vertexDictionary
        vertexDict = {}
        verticesList = list(set(verticesList))
        if len(vertexDictionary) > 0:
            for i in range(1, len(verticesList) + 1):
                if verticesList[i - 1] in vertexDictionary.values():
                    for key, value in vertexDictionary.items():
                        if value == verticesList[i - 1]:
                            vertexDict.update({key: verticesList[i - 1]})
                else:
                    vertexDictionary.update({count: verticesList[i - 1]})
                    vertexDict.update({count: verticesList[i - 1]})
                    count += 1
        else:
            for i in range(1, len(verticesList) + 1):
                vertexDictionary.update({count: verticesList[i - 1]})
                vertexDict.update({count: verticesList[i - 1]})
                count += 1
        for j in range(len(vertexDictionary)):
            for key, value in vertexDictionary.items():
                if value not in verticesList:
                    del vertexDictionary[key]

        return vertexDict

    def printVertex(self, vertexDic):
        vertexStr = "V = {\n  "
        for key, value in vertexDic.items():
            vertexStr = vertexStr + str(key) + ": " + str(value) + "\n  "
        vertexStr = vertexStr + "}"
        print vertexStr

    def setEdgeDic(self, inter, p11, p12, p21, p22, streetName11, streetName21):
        global edgeDictionary
        if len(edgeDictionary) > 1:
            edgeDictStreetName = edgeDictionary.keys()
            if edgeDictStreetName.count(streetName11) == 1:
                lst1 = edgeDictionary[streetName11]
                lst1 = lst1 + [p11, inter, p12]
                edgeDictionary.update({streetName11: lst1})
            else:
                edgeDictionary.update({streetName11: [p11, inter, p12]})
            if edgeDictStreetName.count(streetName21) == 1:
                lst1 = edgeDictionary[streetName21]
                lst1 = lst1 + [p21, inter, p22]
                edgeDictionary.update({streetName21: lst1})
            else:
                edgeDictionary.update({streetName21: [p21, inter, p22]})
        else:
            edgeDictionary.update({streetName11: [p11, inter, p12]})
            edgeDictionary.update({streetName21: [p21, inter, p22]})
        return edgeDictionary

    def setEdgeDicUpated(self, inter1, inter2, p1, p2, streetName, flag):
        global edgeDictionary
        if len(edgeDictionary) > 1:
            edgeDictStreetName = edgeDictionary.keys()
            if edgeDictStreetName.count(streetName) == 1:
                lst1 = edgeDictionary[streetName]
                lst1 = lst1 + [p1, inter1, p2] + [p1, inter2, p2]
                edgeDictionary.update({streetName: lst1})
            else:
                edgeDictionary.update({streetName: [p1, inter1, p2, p1, inter2, p2]})
        else:
            edgeDictionary.update({streetName: [p1, inter1, p2, p1, inter2, p2]})
        return edgeDictionary

    def removeDuplicate(self, edgeDictionary):
        keys = edgeDictionary.keys()
        for i in range(len(keys)):
            val = edgeDictionary[keys[i]]
            duplicateList = []
            limit = len(val) / 3
            lst = []
            for j in range(len(val)):
                lst.append(val[j])
                if ((j + 1) % 3 == 0):
                    duplicateList.append(lst)
                    lst = []
            uniqueList = []
            for sublist in duplicateList:
                if sublist not in uniqueList:
                    uniqueList.append(sublist)
            edgeDictionary.update({keys[i]: uniqueList})
        return edgeDictionary

    def setEdges(self, edgeDictionary, vertexDictionary):
        edgeListNew = []
        for i in range(len(edgeDictionary.keys())):
            val = edgeDictionary.values()[i]
            for j in range(len(val)):
                for k in range(len(val[j]) - 1):
                    valueStr = ""
                    for key, value in vertexDictionary.items():
                        if val[j][k] == value:
                            valueStr = valueStr + str(key) + ","
                    for key, value in vertexDictionary.items():
                        if val[j][k + 1] == value:
                            valueStr = valueStr + str(key) + ","
                    valueStr = "<" + valueStr[:-1] + ">"
                    edgeListNew.append(valueStr)
        return edgeListNew

    def removeDuplicateEdgeList(self, edgeList):
        edgeListNew = []
        edgeListNew1 = []
        flag = False
        for i in range(len(edgeList)):
            element = edgeList[i]
            lst = element[1:][:-1].split(",")
            if lst[0] == lst[1]:
                pass
            else:
                edgeListNew.append(edgeList[i])
        for j in range(len(edgeListNew) - 1):
            element_1 = edgeListNew[j]
            lst1 = element_1[1:][:-1].split(",")
            for k in range(j, len(edgeListNew)):
                element_2 = edgeListNew[k]
                lst2 = element_2[1:][:-1].split(",")
                if lst1[0] == lst2[1] and lst1[1] == lst2[0]:
                    flag = True
                    break
                else:
                    flag = False
            if flag is False:
                edgeListNew1.append(element_1)
        if not edgeListNew:
            pass
        else:
            edgeListNew1.append(edgeListNew[len(edgeListNew) - 1])
        return edgeListNew1

    def validateInter(self, edgeDictionary):
        edgeDictionaryNew = {}
        keys = edgeDictionary.keys()
        for i in range(len(keys)):
            value = edgeDictionary[keys[i]]
            if (len(value) >= 2):
                listNew = []
                while len(edgeDictionary[keys[i]]) != 0:
                    k = 1
                    j = 2
                    while k < len(value):
                        if value[0][0] == value[k][0] and value[0][j] == value[k][2]:
                            for s in range(len(value[0]) - 1):
                                ptList1 = value[0][s].split(",")
                                ptList2 = value[0][s + 1].split(",")
                                x1 = float((ptList1[0][1:]))
                                y1 = float((ptList1[1][:-1]))
                                x2 = float(ptList2[0][1:])
                                y2 = float(ptList2[1][:-1])
                                ptList3 = str(value[k][1:][:-1][0][1:][:-1]).split(",")
                                x3 = float(ptList3[0])
                                y3 = float(ptList3[1])
                                d1 = float(math.sqrt((x1 - x3) ** 2 + (y1 - y3) ** 2))
                                d2 = float(math.sqrt((x2 - x3) ** 2 + (y2 - y3) ** 2))
                                dist = float(math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2))
                                distStr = d1 + d2
                                if abs(distStr - dist) < 0.001:
                                    lst = []
                                    lst.append(value[k][1])
                                    value[0] = value[0][:s + 1] + lst + value[0][s + 1:]
                                    break
                            del value[k]
                            j = j + 1
                        else:
                            k = k + 1
                    listNew.append(value[0])
                    del value[0]
                edgeDictionaryNew.update({keys[i]: listNew})
            else:
                edgeDictionaryNew.update({keys[i]: value})
        return edgeDictionaryNew

    def printEdges(self, edgeList):
        edgeString = "E = { \n  "
        for i in range(len(edgeList)):
            edgeString = edgeString + str(edgeList[i]) + ",\n  "
        edgeString = edgeString[:-4] + "\n}"
        print edgeString


obj = Graph()
obj.main()