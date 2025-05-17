#Emiliano Delgadillo Osorio
#14 de Mayo de 2025
#Syntax Highler
#Made with help of
# Regex tutorial - 4Geeks
# "Lexical Analysis with Elixir: Building a Language Highlighter"
# "Recursive Descent Tokenization for Syntax Highlighting"

defmodule Cppreader do
  def regex do
    [
      # // ó /* */
      [~r/^(\/\/\s*[a-zA-Z0-9]+.*)|(\/\*[\s\S]*?\*\/)/, :comments],

      # "Hola Mundo", "manzana"
      [~r/^"(?:[^"\\]|\\.)*"/, :strings],

      # 'a'
      [~r/^[a-zA-Z0-9]/, :char],

      # int, class, if, else, while, int, for, with, as , import
      [~r/^(int|float|double|char|bool|if|else|for|while|return|class|struct|public|private|protected|namespace|using|std|string|include)\b/, :keywords],

      # 42, 3.14, 1e-19
      [~r/^([0-9]+(\.[0-9]+)?([eE][-+]?[0-9]+)?)\b/, :numbers],

      # miVariable, _temp
      [~r/^[a-zA-Z_]\w*/, :identifiers],

      # funciones como miVariable()
      [~r/^[a-zA-Z_]\w*(?=\s*\()/, :functions],

      # +,-,*,/,=
      [~r/^(\+\+|--|->|\+=|-=|\*=|\/=|%=|&=|\|=|\^=|<<=|>>=|==|!=|<=|>=|&&|\|\||\.\*|->|\+|-|\*|\/|%|=|<|>|!|~|\^|&|\||<<|>>|\.|::|\?:|\?|:)/, :operator],

      # ; , { }
      [~r/^(\{|\}|\(|\)|\[|\]|;|,|\.|\->|::)/, :punctuation],

      # -----
      [~r/^\s+/, :whitespace],

      # #include
      [~r/^#include\b/, :librarys],

      # <iostream>, <math>
      [~r/^<[a-z]+>/, :library2]
    ]
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
    lines = String.split(content, ~r/\r?\n/)

    # Procesar cada línea
    html =
      lines
      |> Enum.map(&process_line/1)
      |> Enum.join("\n")

    # Escribe el archivo de regreso
    gen_html = format_html(html)
    output_file = "output.html"

    File.write!(output_file, gen_html)
    IO.puts("Successful analysis")

    gen_html
  end

  defp process_line(line) do
    readytoken(line, regex(), [])
    |> Enum.join("")
  end

  defp searchtoken([[pattern,type] | tail], string) do
    find = Regex.run(pattern,string)
    cond do
      find == nil -> searchtoken(tail, string)
      find != nil -> [find, type]
    end
  end

  defp searchtoken([], string) do
    # Si ningún patrón coincide, tomar el primer carácter como desconocido
    first_char = String.slice(string, 0, 1)
    [[first_char], :unknown]
  end

  defp readytoken("", _token_patterns, acc) do
    Enum.reverse(acc)
  end

  defp readytoken(line, token_patterns, acc) do
    [found, type] = searchtoken(token_patterns, line)

    stringg = if is_list(found), do: hd(found), else: found
    fixed_str = stringg
    |> String.replace("&", "&amp;")
    |> String.replace("<", "&lt;")
    |> String.replace(">", "&gt;")
    |> String.replace("\"", "&quot;")

    lenght = String.length(stringg)

    if lenght == 0 do Enum.reverse(acc)
    else
      {_nonecessary, rest} = String.split_at(line,lenght)

      readytoken(rest, token_patterns, [
        "<span class=\"#{type}\">" <> fixed_str <> "</span>" | acc
      ])
    end
  end

  # Formatea el HTML completo - adaptado de la función format existente
  defp format_html(body) do
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

  # Separar el archivo en tokens
  def tokenize(content) do
    identify_tokens(content, [])
  end

  def identify_tokens("", tokens), do: Enum.reverse(tokens)
  def identify_tokens(content, tokens) do
    patterns = regex()

    case find_next_token(content, patterns) do
      {type, match, rest} ->
        identify_tokens(rest, [{type, match} | tokens])
      nil ->
        # Cuando no haga match avanzamos un carácter
        {next_char, rest} = String.split_at(content, 1)
        identify_tokens(rest, [{:unknown, next_char} | tokens])
    end
  end

  def find_next_token(content, patterns) do

    patterns_list = Enum.map(patterns, fn [pattern, type] -> {type, pattern} end)
    # Encuentra el siguiente token en el contenido
    Enum.reduce_while(patterns_list, nil, fn {type, pattern}, _acc ->
      case Regex.run(pattern, content, capture: :first) do
        [match] ->
          rest = String.replace_prefix(content, match, "")
          {:halt, {type, match, rest}}
        nil ->
          {:cont, nil}
      end
    end)
  end

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
      |> String.replace("\"", "&quot;")

    "<span class=\"#{type}\">#{escaped_content}</span>"
  end
end
