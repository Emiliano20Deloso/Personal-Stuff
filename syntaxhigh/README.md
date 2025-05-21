# Syntax Highlighter in Elixir for C++

In this task I made a program call (`syntaxhigh.exs`) in elixir who receive a `.cpp` file with a normal C++ code, then it analize and with regular expression it could take every single token from c++ in the file:

- Keywords
- Comments
- Strings
- Libraries 
- Numbers 
- Identifiers
- Functions 
- Punctuations
- Whitespace 
- Operators

The target is to make a `.html` file (`output.html`) where you can see every different token in a specific color. 

## Files Required

The files you need to run this are: 
- `syntaxhigh.exs`
- `prueba2.cpp`
- `prueba3.cpp`
- `Store_proyect.cpp` 
- `output.html` 

The 3 `.cpp` files are for testing.

# Complexity Analysis of Syntax Highlighter in Elixir

1. **Function Regex**
   -The complexity that I calculate for this specifical function is O(1) because it is simply where we declared our regular expressions and it returns just the same. 

2. **Function Read**
   -For this function, base on it purpose I would say that we have a O(n)complexity, this because we are reading a file that could consist on a simply 3 line code or a big one with 1000 lines of code.  

3. **Function Analyze**
   -Analyze fullfils the function to split every line of the .cpp file that we are testing, in addition is also join the lines that are already processed and generate the .html file, considering all of this, the complexity is O(N^2).


4. **Function process_line**
   -In this case considering that the function check the regex list 1 by 1, I can say it is an O(1), at the same time we are talking about a recursive function, which means it checks every single line of the code till it fine something that fits in, so at the end the complexity is O(n^2)

In resume this program have a total complexity of O(n^2) because much of the complexity is base on how long is the file that we are testing, in other words, if the file to be analize is shorter this could reduce the complexity since we don´t have to analyze that much tokens, reducing the complexity maybe to a O(n)
#

# Possible Optimizations

## Performance Improvements

1. **Regex Pattern Ordering**
   - Sort regex patterns by frequency of appearance to improve average time
   - Most common patterns should be checked first

2. **Efficient Tokenization**
   - Implement more efficient tokenization techniques
   - Avoid testing all patterns for each position
   - Use pattern matching optimization strategies

3. **Finite State Machine Implementation**
   - Implement a parser based on finite state machines
   - This would reduce complexity
   - More efficient than regex pattern matching for certain cases

## Benefits

- Reduced processing time
- Lower memory usage
- More efficient token recognition
- Better scalability for larger files

# Ethical Implications

The ethical implications of this type of technology in society are that this can be a great help for someone who is trying to make a similar project but in another language, in addition to the fact that this also facilitates the understanding of how a programming language works in terms of knowing how to identify all its elements and at the same time makes it so that by just looking at a code you can much more easily identify what the person who wrote it meant to say.