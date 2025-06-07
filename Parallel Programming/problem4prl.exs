#Emiliano Delgadillo Osorio
#3 de Junio de 2025
#Parallel programming and concurrent programming
#Problem #4 Parallel

defmodule BasicTasks do
  @doc """
  Toy examples of how to use the Task module and its functions
  """
  # Function to be called by the threads
  def palindrome_checker(id) do
    IO.puts("Hello from thread id #{id}")
    if SuperPalindromeCount.is_bin_hex_palindrome(id), do: 1, else: 0
  end

  # Launch a task and forget about it
  def test1() do
    IO.puts("MAIN THREAD START")
    Task.start(fn -> palindrome_checker(0) end)
    Task.start(fn -> palindrome_checker(1) end)
    Task.start(fn -> palindrome_checker(3) end)
    Task.start(fn -> palindrome_checker(5) end)
    IO.puts("MAIN THREAD FINISH")
  end

  # Launch a task and wait for it to finish
  def test2() do
    IO.puts("MAIN THREAD START")
    task1 = Task.async(fn -> palindrome_checker(0) end)
    task2 = Task.async(fn -> palindrome_checker(1) end)
    task3 = Task.async(fn -> palindrome_checker(3) end)
    task4 = Task.async(fn -> palindrome_checker(5) end)
    _res1 = Task.await(task1)
    |> IO.inspect()
    _res2 = Task.await(task2)
    |> IO.inspect()
    _res3 = Task.await(task3)
    |> IO.inspect()
    _res4 = Task.await(task4)
    |> IO.inspect()
    IO.puts("MAIN THREAD FINISH")
  end

  # Launch multiple threads
  def test3(n) do
    IO.puts("MAIN THREAD START")
    1..n
    |> Enum.map(&Task.async(fn -> palindrome_checker(&1) end))
    |> Enum.map(&Task.await(&1))
    |> IO.inspect()
    IO.puts("MAIN THREAD FINISH")
  end
end

defmodule SuperPalindromeCount do
  @moduledoc """
  Computations to count bin-hex-palindromes less than 2^n either in sequence or in parallel
  """

  @doc """
  Check if a number is a bin-hex-palindrome
  """
  def is_bin_hex_palindrome(n) do
    binary = Integer.to_string(n, 2)
    hex = Integer.to_string(n, 16)
    is_palindrome(binary) and is_palindrome(hex)
  end

  defp is_palindrome(str) do
    str == String.reverse(str)
  end

  @doc """
  Simple version of a palindrome count function that works sequentially
  """
  def palindrome_count(n), do: do_palindrome_count(0, :math.pow(2, n) |> trunc(), 0)

  defp do_palindrome_count(current, limit, acc) when current >= limit, do: acc
  defp do_palindrome_count(current, limit, acc) do
    if is_bin_hex_palindrome(current) do
      do_palindrome_count(current + 1, limit, acc + 1)
    else
      do_palindrome_count(current + 1, limit, acc)
    end
  end

  @doc """
  Function to count all bin-hex-palindromes between 'start' and 'stop'.
  This will be used to find a part of a whole palindrome count.
  """
  def palindrome_count_range({start, stop}), do: do_palindrome_count_range(start, stop, 0)

  defp do_palindrome_count_range(start, stop, acc) when start > stop, do: acc
  defp do_palindrome_count_range(start, stop, acc) do
    if is_bin_hex_palindrome(start) do
      do_palindrome_count_range(start + 1, stop, acc + 1)
    else
      do_palindrome_count_range(start + 1, stop, acc)
    end
  end

   @doc """
  Compute the count of bin-hex-palindromes using multiple threads
  """
  def palindrome_count_parallel(n, threads) do
    limit = :math.pow(2, n) |> trunc()
    step = div(limit, threads)
    # Create the lists of starting and ending values for the ranges
    starts = make_range(0, step, threads)
    stops = make_range(step - 1, step, threads)
    # Adjust the last stop to be exactly limit - 1
    stops = List.replace_at(stops, -1, limit - 1)

    # Join the lists into a list of tuples
    Enum.zip(starts, stops)
    # |> IO.inspect()
    # Send each of the tuples to its own task to compute a partial count
    |> Enum.map(&Task.async(fn -> palindrome_count_range(&1) end))
    # Wait for the results. They will become a list
    |> Enum.map(&Task.await(&1, :infinity))
    # |> IO.inspect()
    # Sum all the elements of the list to get the final result
    |> Enum.reduce(0, &(&1 + &2))
  end

  @doc """
  Create a list with values that start at 'init', and increment by 'step'
  as many times as 'iter'
  """
  def make_range(init, step, iters), do: do_make_range(init, step, iters, [])

  defp do_make_range(_init, _step, 0, res), do: Enum.reverse(res)
  defp do_make_range(init, step, iter, res), do: do_make_range(init + step, step, iter - 1, [init | res])
end

defmodule Main do
  def main(args) do
    # Check how many arguments were sent
    case args do
      # One argument, compute the palindrome count sequentially
      [n] ->
        SuperPalindromeCount.palindrome_count(String.to_integer(n))
        |> IO.inspect(label: "Sequential count of bin-hex-palindromes for n=#{n}")

      [n, t] ->
        SuperPalindromeCount.palindrome_count_parallel(String.to_integer(n), String.to_integer(t))
        |> IO.inspect(label: "Parallel count of bin-hex-palindromes for n=#{n}")
      _ ->
        IO.puts("Usage: \n $ elixir bin_hex_palindrome.exs <n> <threads>")
    end
  end
end

# Call the main function with the arguments used in the command line
Main.main(System.argv())
