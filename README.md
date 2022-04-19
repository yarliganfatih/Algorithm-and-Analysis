# Algorithm-and-Analysis

## Introduction

The text is analyzed according to question patterns and conjunctions and tries to find an answer to the question sought.

In this project we construct a simple question answering system. We implement a program which displays an answer for any question such as in the given text questions. Two input files used in our algorithm. First one which includes a text, and second one containing questions. While our program is executed, it automatically generates an answer for each question in the questions.txt file using the the_truman_show_script.txt file as main text. Our program outputs to the console in this way, first giving the question with the number of that and then the answer below the question.

## Methods
We used C++ as a programming language and the libraries that we used are C++ STL iostream,string, unordered_map, fstream, and ctime for calculating the runtime of the code. We did not use any third party library. For the searching part we used Horspool's Algorithm method. We used the string matching method to split the words.

### Algorthim’s step by step implementation is shown below:
- Read one by one by splitting the sentences in the_truman_show_script.txt" by dot.
- Read one by one by splitting the questions in questions.txt" by question mark.
- Keep questions and sentences in global arrays for use in oops and functions.
- Split question by question pattern (Wh- array).
- Scan with Horspool’s Algorithm the parts of the divided uestion by decrementing the words until you find them in he sentences.
- Also, for a better search, the horspool algorithm we use ompares the parameters it receives by reducing them to owercase.
- Give the answer by finding and parsing in the sentence he words in the question and the extra words (in arrays).
- Skip to the next question.


## Time Complexity
First of all, we processed the 'the_truman_show_script.txt' file. To complete this, we loop through the text, dividing the sentences in the script between dots. If we say that there are 'm' sentences between two points, the time complexity will be O(m). After that, we processed the questions. We also divided the questions according to question marks. If we take the
average total number of characters in a question as 'q' and the number of question marks as 'n', we get the time complexity of O(n*q). Then we divide the question according to the question pattern. Let's call the number of new characters in the script 'l'. We used Horspool's Algorithm for each question. The average time complexity of the Horspool Algorithm for a question is O(1). The time complexity of each of our questions separated by question marks is O(n*l). As a result, if we consider the time complexity; O(m) + O(n*q) + O(n*l)'. It would be O(n*l). Our time complexity is O(n*l).


## Average Speed and Correctness of Algorithm
We have run the algorithm 5 times to calculate the average runtime of the algorithm. The CPU that we utilized is **AMD Ryzen™5 3500X 3.6GHz 32MB 65W 7nm (6CPUs)**. In calculating the average speed part we have just answered the given question by project and the algorithm’s runtimes are 0.054s , 0.06s , 0.055s , 0.056s , 0.054s. Then the average is 0,0558 seconds. In the test step, we tried 15 different questions, including the questions of the project and all the question answers were correct. (15/15)


## Testing

### inputs :

text => `the_truman_show_script.txt`

questions => `questions.txt`

### outputs :

```
1) Who is suddenly aware that the hundreds of other beachgoers have stopped their activities to stare at him?
Truman
2) With an apathetic shrug, what does Truman replace?
receiver
3) He picks up the framed picture of his wife from where?
desk
4) The sound of the children triggers what in his head?
memory
5) What does Truman exit to investigate?
Oldsmobile
6) How many girls look up, surprised by the interruption?
3
7) What time is read on a clock on the wall?
4:12pm
8) What color is the cardigan she is already removing from the drycleaning bag on the 
back seat as Truman pulls away from the curb?
lavender
9) How does Truman rest his hand on the bed?
tentatively
10) What did they have come to last in the final row?
bus 
11) Which paper bag does Truman pass her without reply?
brown
12) Where does a dressing room contain a long row of identical mirrored make-up tables?
cavernous
13) What does Truman eat alone on a concrete bench in a cement park?
lunch
14) What is attached to speakers on tall stands facing the ventilation ducts?
recorder
15) How does Truman nod at the memory?
fondly
```
