#Emiliano Delgadillo Osorio
#14 de Mayo de 2025
#Syntax Highler

defmodule Cppreader do
  def cpp_token_patterns do
    %{
      # // ó /* */
      comments: ~r/^(\/\/.*?$|\/\*[\s\S]*?\*\/)/m,

      # "Hola Mundo", "manzana"
      strings: ~r/^"(?:\\.|[^"\\])*"/,

      # 'a'
      char: ~r/^'(?:\\.|[^'\\])'/,

      # int, class, if, else, while, int, for, with, as , import
      keywords: ~r/^(int|float|double|char|bool|if|else|for|while|return|class|struct|public|private|protected|namespace|using|std|string|include)\b/,

      # 42, 3.14, 1e-19
      numbers: ~r/^([0-9]+(\.[0-9]+)?([eE][-+]?[0-9]+)?)\b/,

      # miVariable, _temp
      identifiers: ~r/^[a-zA-Z_]\w*/,

      # funciones como miVariable()
      functions: ~r/^[a-zA-Z_]\w*(?=\s*\()/,

      # +,-,*,/,=
      operator: ~r/^(\+|\-|\*|\/|=|==|!=|<|>|<=|>=|&&|\|\||\!|\%|\^|\&|\|)/,

      # ; , { }
      punctuation: ~r/^(;|,|\{|\}|\(|\)|\[|\]|:|\.)/,

      # -----
      whitespace: ~r/^\s+/,

      # #include
      librarys: ~r/^#include\b/,

      # <iostream>, <math>
      library2: ~r/^<[a-z]+>/
    }
  end

  # Lee el archivo de entrada (.cpp)
  def read(path) do
    case File.read(path) do
      {:ok, content} -> analyze(content)
      _ -> IO.puts("Could not find the file")
    end
  end

  # Analiza el contenido de .cpp
  def analyze(content) do
    tokens = tokenize(content)
    gen_html = format(tokens)
    output_file = "output.html"

    # Escribe el archivo de regreso
    File.write!(output_file, gen_html)
    IO.puts("Successful analysis")
  end

  # Separa el archivo en tokens
  def tokenize(content) do
    identify_tokens(content, [])
  end

  # Función recursiva para identificar tokens
  def identify_tokens("", tokens), do: Enum.reverse(tokens)
  def identify_tokens(content, tokens) do
    patterns = cpp_token_patterns()

    case find_next_token(content, patterns) do
      {type, match, rest} ->
        identify_tokens(rest, [{type, match} | tokens])
      nil ->
        # Cuando no haga match avanzamos un carácter
        {next_char, rest} = String.split_at(content, 1)
        identify_tokens(rest, [{:unknown, next_char} | tokens])
    end
  end

  # Encuentra el siguiente token en el contenido
    def find_next_token(content, patterns) do
      Enum.reduce_while(Map.to_list(patterns), nil, fn {type, pattern}, _acc ->
        case Regex.run(pattern, content, capture: :first) do
          [match] ->
            rest = String.replace_prefix(content, match, "")
            {:halt, {type, match, rest}}
          nil ->
            {:cont, nil}
        end
      end)
    end
N
  @doc """
  Recibe la lista de tokens y envuelve cada token en un <span>.
  """
  def format(tokens) when is_list(tokens) do
    body =
      tokens
      |> Enum.map(&create_html/1)
      |> Enum.join("")

    """
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <title>C++ Code Analysis</title>
      <style>
        .comments    { color: #808080; }
        .strings     { color: #008000; }
        .char        { color: #008000; }
        .keywords    { color: #0000ff; font-weight: bold; }
        .numbers     { color: #800080; }
        .identifiers { color: #000000; }
        .functions   { color: #000080; font-weight: bold; }
        .operator    { color: #ff0000; }
        .punctuation { color: #ff6600; }
        .librarys    { color: #800000; font-weight: bold; }
        .library2    { color: #008080; }
        .unknown     { color: #000000; }
        .whitespace  { color: transparent; }
        body         { font-family: Arial, sans-serif; margin: 20px; }
        pre          { background-color: #f5f5f5; padding: 15px; border-radius: 5px; font-family: monospace; }
      </style>
    </head>
    <body>
      <h1>Análisis de Código C++</h1>
      <pre>#{body}</pre>
    </body>
    </html>
    """
  end

  # Crea el span HTML para un token
  def create_html({type, content}) do
    escaped_content = content
      |> String.replace("&", "&amp;")
      |> String.replace("<", "&lt;")
      |> String.replace(">", "&gt;")

    "<span class=\"#{type}\">#{escaped_content}</span>"
  end
end
