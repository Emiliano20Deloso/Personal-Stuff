#Emiliano Delgadillo Osorio
#3 de Junio de 2025
#Parallel programming and concurrent programming
#Problem #2 Parallel

defmodule BasicTasks do
  @doc """
  Toy examples of how to use the Task module and its functions
  """
  # Function to be called by the threads
  def prime_checker(id) do
    IO.puts("Hello from thread id #{id}")
    if is_prime(id), do: id, else: 0
  end

  # Launch a task and wait for it to finish
  def test1() do
    IO.puts("MAIN THREAD START")
    Task.start(fn -> prime_checker(2) end)
    Task.start(fn -> prime_checker(3) end)
    Task.start(fn -> prime_checker(5) end)
    Task.start(fn -> prime_checker(7) end)
    IO.puts("MAIN THREAD FINISH")
  end

  # Launch a task and wait for it to finish
  def test2() do
    IO.puts("MAIN THREAD START")
    task1 = Task.async(fn -> prime_checker(2) end)
    task2 = Task.async(fn -> prime_checker(3) end)
    task3 = Task.async(fn -> prime_checker(5) end)
    task4 = Task.async(fn -> prime_checker(7) end)
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
    |> Enum.map(&Task.async(fn -> prime_checker(&1) end))
    |> Enum.map(&Task.await(&1))
    |> IO.inspect()
    IO.puts("MAIN THREAD FINISH")
  end
end

defmodule SuperPrimeSum do
  @moduledoc """
  Computations to find the sum of all prime numbers up to n either in sequence or in parallel
  """

  @doc """
  Check if a number is prime
  """
  def is_prime(x) when x < 2, do: false
  def is_prime(2), do: true
  def is_prime(x) do
    limit = :math.sqrt(x) |> trunc()
    not Enum.any?(2..limit, fn i -> rem(x, i) == 0 end)
  end

  @doc """
  Simple version of a prime sum function that works sequentially
  """
  def prime_sum(n), do: do_prime_sum(2, n, 0)

  defp do_prime_sum(current, n, acc) when current > n, do: acc
  defp do_prime_sum(current, n, acc) do
    if is_prime(current) do
      do_prime_sum(current + 1, n, acc + current)
    else
      do_prime_sum(current + 1, n, acc)
    end
  end

  @doc """
  Function to sum all prime numbers between 'start' and 'stop'.
  This will be used to find a part of a whole prime sum.
  """
  def prime_sum_range({start, stop}), do: do_prime_sum_range(start, stop, 0)

  defp do_prime_sum_range(start, stop, acc) when start > stop, do: acc
  defp do_prime_sum_range(start, stop, acc) do
    if is_prime(start) do
      do_prime_sum_range(start + 1, stop, acc + start)
    else
      do_prime_sum_range(start + 1, stop, acc)
    end
  end

  @doc """
  Compute the sum of primes of a number using multiple threads
  """
  def prime_sum_parallel(n, threads) do
    step = div(n - 1, threads)  # Start from 2, so subtract 1
    # Create the lists of starting and ending values for the ranges
    starts = make_range(2, step, threads)
    stops = make_range(2 + step - 1, step, threads)
    stops = List.replace_at(stops, -1, n)

    # Join the lists into a list of tuples
    Enum.zip(starts, stops)
    # |> IO.inspect()
    # Send each of the tuples to its own task to compute a partial sum
    |> Enum.map(&Task.async(fn -> prime_sum_range(&1) end))
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
      # One argument, compute the prime sum sequentially
      [n] ->
        SuperPrimeSum.prime_sum(String.to_integer(n))
        |> IO.inspect(label: "Sequential sum of primes: #{n}")
        [n, t] ->
          SuperPrimeSum.prime_sum_parallel(String.to_integer(n), String.to_integer(t))
          |> IO.inspect(label: "Parallel sum of primes: #{n}")
      _ ->
        IO.puts("Usage: \n $ elixir prime_sum.exs <n> <threads>")
    end
  end
end

# Call the main function with the arguments used in the command line
Main.main(System.argv())
