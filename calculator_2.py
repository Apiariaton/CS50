



#Plan to make a working calculator that cleans text
#0. Create an object which is going to be the parameter which is entered into each respective function


class QA:
   invalid_sequence = ["/*","*/","**","++","--", "+-","-+"]
   corrections = {"/*":"/","*/":"*","**":"*","++":"+","--":"+", "+-":"-","-+":"+"}
   acceptable_characters = ["0","1","2","3","4","5","6","7","8","9","-","+","/","*"]
   operators = ["/","*","+","-"]


   total_questions = 0
   description = "Mathematical question and answer"
   def __init__(self): #Raw string, valid character string, math valid string, answer
      self.raw_string = input("Enter sequence to be calculated (Accepted: * / + - numbers, only)")
      self.valid_char_string = self.raw_string
      self.answer = 0

   def validify(self):
      print("Pop",self.valid_char_string)
      pos = 0
      #1. Turn my string to list
      clean_list = list(self.valid_char_string)
      clean_list = filter(lambda a: a in QA.acceptable_characters, clean_list)

      merged = "".join(clean_list)
      print("Merged:",merged)
      for value_pair in QA.corrections:
         merged = merged.replace(value_pair,QA.corrections[value_pair])
      print("Merged:",merged)

      self.valid_char_string = merged
      print("Pop",self.valid_char_string)

   def operate(self,character_value, operand_1,operand_2):
      print("The character value passed into operate is: ",character_value)
      print(f"operand_1: {operand_1} \n operand_2: {operand_2}")
      if character_value == "+":
         return str(operand_1 + operand_2)
      elif character_value == "-":
         return str(operand_1 - operand_2)
      elif character_value == "*":
         return str(operand_1 * operand_2)
      elif character_value == "/":
         return str(operand_1 / operand_2)

   """
   Test cases
   1: 2 + 2
   2: 2+2www-234
   3: 2 * 3 + 2
   4: 2 + 5 - 3 * 6 w
   5: 2 + 5 + 342 -234  / /
   """


   def evaluate(self):
      for value in QA.operators:
         print(value)
         def minus_count():
            minus_count = 0
            operator_count = 0
            pos = 0
            for n in self.valid_char_string:
               if n in QA.operators:
                  operator_count += 1
                  if n == "-":
                     minus_count += 1
                     try:
                        if pos > 0:
                           check_me = self.valid_char_string[pos - 1]
                           if check_me.isdigit() == True:
                              return 1
                     except ValueError:
                        pass
               pos += 1
            if minus_count <= 1 and operator_count <= 1:
               return 0
            else:
               return 1

         while value in self.valid_char_string and minus_count() != 0:
            print("Yes")
            centre = self.valid_char_string.index(value)
            up = centre + 1
            up_s = up
            down = centre - 1
            down_s = down
            while up < len(self.valid_char_string) - 1 and self.valid_char_string[up + 1] in QA.acceptable_characters[0:10]:
               up += 1
            while down > 0 and self.valid_char_string[down - 1] in QA.acceptable_characters[0:10]:
               down -= 1
            if centre - 1 == down:
               o_1 = int(self.valid_char_string[down])
            else:
               o_1 = int(self.valid_char_string[down:centre])

            if centre + 1 == up:
               o_2 = int(self.valid_char_string[up])
            else:
               o_2 = int(self.valid_char_string[up_s:up + 1])
            print("This is the value of self.valid_char_string", self.valid_char_string)
            replacer = QA.operate(self,value,o_1,o_2)
            self.valid_char_string = self.valid_char_string.replace(self.valid_char_string[down:up + 1],replacer)
      self.answer = int(self.valid_char_string)
      print("Final answer: ",self.answer)


   """
            mid_point = self.valid_char_string.index(value)
            up_point = mid_point

            character = list(self.valid_char_string)

            while up_point < len(self.valid_char_string) - 2 and 48 <= ord(character[up_point + 1]) <= 58:
               #48 - 57 numbers ||
               up_point += 1
               print("up_point is: ", up_point)

            low_point = mid_point
            while low_point >= 1  and 48 <= ord(character[low_point - 1]) <= 58:
               #48 - 57 numbers ||
               low_point -= 1
               print("low_point is: ", low_point)

            if mid_point - low_point == 1:
               operand_1 = int(character[low_point])
            else:
               low_range = character[low_point:mid_point]
               op1_string = ""
               print("Low range values")
               for x in low_range:
                  op1_string += str(x)
                  print(x)
               operand_1 = int(op1_string)

            if up_point - mid_point == 1:
               operand_2 = int(character[up_point])
            else:
               high_range = character[mid_point:up_point]
               op2_string = ""
               print("High range values")
               for x in high_range:
                  op2_string += str(x)
                  print(x)
               operand_2 = int(op2_string)

            replacement_value = self.operate(character[mid_point],operand_1, operand_2)
            print(replacement_value)
            print(self.valid_char_string[low_point:up_point + 1])
            pos = 0
            for x in character[0:low_point]:
               alter_string[pos] = str(x)
               pos += 1
            alter_string[pos:pos + len(replacement_value)] = replacement_value
            pos += len(replacement_value)
            for x in character[up_point:len(character)]:
               alter_string[pos] = str(x)
               pos += 1
            self.valid_char_string = alter_string
            #self.valid_char_string = self.valid_char_string.replace(self.valid_char_string[low_point:up_point + 1],replacement_value)
         self.answer = int(self.valid_char_string)
         """



objs = [QA() for i in range(3)]
for i in objs:
   QA.validify(i)
   QA.evaluate(i)
   print(i.valid_char_string)




#1. Create function to remove non-valid characters, which outputs cleaned output
#2. Create function that lists which operations are included within the cleaned output and returns the output and the relevant operations
#3. Create function which consolidates the values, by performing an operation, then replacing the existing values until there are no more operators, only operands or one minus
#4. Create function which outputs this value