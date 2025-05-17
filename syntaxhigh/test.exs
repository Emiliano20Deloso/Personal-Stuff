# Cargar el módulo
Code.require_file("syntaxhigh.exs")

# Verificar que el archivo existe
IO.puts "Verificando archivo prueba2.cpp..."
case File.exists?("prueba2.cpp") do
  true ->
    IO.puts "Archivo encontrado, procediendo con el análisis..."
    Cppreader.read("prueba2.cpp")
  false ->
    IO.puts "Error: No se encontró el archivo prueba2.cpp"
end
