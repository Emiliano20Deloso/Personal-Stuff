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
- `test.exs` 

The 3 `.cpp` files are for testing.

# Complexity Analysis of Syntax Highlighter in Elixir

## Main Functions and their Complexity

### 1. read/1
- **Complexity**: O(1) for file reading
- The actual complexity depends on analyze/1

### 2. analyze/1
- **Complexity**: Depends on tokenize/1 and format/1
- File writing is O(n) where n is the size of the generated HTML

### 3. tokenize/1 and identify_tokens/2
- **Complexity**: O(m) where m is the length of the source code
- However, the execution of find_next_token/2 in each iteration adds complexity

### 4. find_next_token/2
- **Complexity**: O(k) where k is the number of regex patterns (12 in your implementation)
- For each token, it tries to match with all patterns until finding one

### 5. format/1
- **Complexity**: O(t) where t is the number of tokens
- Each token must be processed to create its corresponding HTML

### 6. create_html/1
- **Complexity**: O(l) where l is the length of the token content
- Special character replacement operations are linear with respect to content size

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




