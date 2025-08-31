using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.Linq;
using System.Numerics;
using System.Text;

namespace ConsoleApp3
{
    class Program
    {
        static List<ulong> S = new List<ulong>();

        static List<ulong> L0 = new List<ulong>();
        static List<ulong> L1 = new List<ulong>();

        static ulong L0TotalSum = 0;
        static ulong L1TotalSum = 0;
        static ulong problemSpace = 0;
        static ulong targetValue = 0;

        static Random rnd = new Random(Environment.TickCount);

        static void Main(string[] args)
        {
            int n = int.Parse(args[0]);
            int p = int.Parse(args[1]);
            int targetLocation = int.Parse(args[2]);

            InitializeWithArgs(args, n, p, targetLocation);

            n = S.Count();

            int finalLocation = (int)((targetValue / (double)problemSpace) * 100);

            Console.WriteLine("Alte-Maui Algorithm - Copyright Jesus Salas 2009-2018");
            Console.WriteLine("Current configuration:");
            Console.WriteLine("");
            Console.WriteLine("\tN = " + n);
            Console.WriteLine("\tP = " + p);
            Console.WriteLine("\td = " + ((double)n / p));
            Console.WriteLine("\tt = " + targetValue);
            Console.WriteLine("\tproblem space = " + problemSpace);
            Console.WriteLine("\tt original location = " + targetLocation);
            Console.WriteLine("\tt final location = " + finalLocation);

            Console.WriteLine("------------------------------------------------");
            Console.WriteLine();

            if (targetValue > problemSpace * 0.5)
            {
                //                targetValue = problemSpace - targetValue;
                finalLocation = (int)((targetValue / (double)problemSpace) * 100);
                Console.WriteLine("\t-> Targeting the lesser: " + targetValue);
                Console.WriteLine("\t-> New zone: " + (int)((targetValue / (double)problemSpace) * 100));
                Console.WriteLine(" ");
                Console.WriteLine("".PadLeft(40, '-'));
            }

            Solver2 step1 = new Solver2();
            Solver2 step2 = new Solver2();
            Solver2 step3 = new Solver2();


            int start = Environment.TickCount;

            System.IO.File.AppendAllLines("ksubsetround.txt", new string[] { $"{n}  ".PadLeft(20, '-') });
            System.IO.File.AppendAllLines("ksubsetroundperline.txt", new string[] { $"{n}  ".PadLeft(20, '-') });

            step3.Solve(new List<ulong>(S), n, p, targetValue, (n / 4), 0, "Standard");

            var S2 = new List<ulong>(S);

            Console.WriteLine("---------------");
            //Console.WriteLine($"{step3.globalKSubsets.ToString("N")}");
            Console.WriteLine("---------------");

            return;
        }


        /// <summary>
        /// k-permutations holder
        /// </summary>
        public class KPerm2
        {
            public KPerm2(ImmutableList<int> pendingElements)
            {

            }

            public KPerm2(BigInteger value, BitArray elements, int split, List<ulong> Set, ImmutableList<int> pendingElements)
            {
                this.value = value;

                this.elements = new BitArray(elements);
                this.split = split;
                this.Set = Set;
                this.pendingElements = pendingElements;
                RecalculateValue();
            }

            public BigInteger value;

            public BitArray elements;
            public int split;
            public List<ulong> Set;
            public ImmutableList<int> pendingElements;

            public BigInteger RecalculateValue()
            {
                BigInteger totalSum = 0;

                int setCount = Set.Count();
                for (int t = this.split; t < elements.Length; t += 2)
                {
                    if (elements.Get(t))
                    {
                        BigInteger temp = Set[t];
                        totalSum += temp;
                    }
                }
                value = totalSum;
                return totalSum;
            }

            public BigInteger AddForVerification()
            {
                BigInteger totalSum = 0;
                List<ulong> toPrint = new List<ulong>();

                for (int t = 0; t < elements.Length; t++)
                {
                    if (elements.Get(t))
                    {
                        toPrint.Add(Set[t]);
                        totalSum += Set[t];

                    }

                }
                Console.WriteLine("\n\t-> subset finally is: " + String.Join(", ", toPrint));
                value = totalSum;
                return totalSum;
            }

            public string[] ElementsList()
            {
                List<string> list = new List<string>();
                for (int t = this.split; t < elements.Length; t += 2)
                {
                    if (elements.Get(t))
                    {
                        list.Add(Set[t].ToString());
                    }
                }
                return list.ToArray();
            }

            public override string ToString()
            {
                BigInteger totalSum = 0;
                List<BigInteger> toPrint = new List<BigInteger>();

                int totalElements = 0;
                for (int t = 0; t < elements.Length; t++)
                {
                    if (elements.Get(t))
                    {
                        toPrint.Add(Set[t]);
                        totalSum += Set[t];
                        totalElements++;
                    }
                }

                return String.Concat("SUM: ", totalSum, " | Split: ", this.split, " | Length: ", totalElements, " | ", String.Join(",", toPrint));
            }

            public string IndexesToString()
            {
                BigInteger totalSum = 0;
                List<string> toPrint = new List<string>();

                int totalElements = 0;
                for (int t = 0; t < elements.Length; t++)
                {
                    if (elements.Get(t))
                    {
                        toPrint.Add(t.ToString());
                        totalSum += Set[t];
                        totalElements++;
                    }
                }

                return String.Concat("SUM: ", totalSum, " | Split: ", this.split, " | Length: ", totalElements, " | ", String.Join(",", toPrint));
            }

            internal void ReverseElements()
            {
                BitArray newElements = new BitArray(Set.Count);
                for (int t = this.split; t < elements.Length; t += 2)
                {
                    if (elements.Get(t) == false)
                    {
                        newElements.Set(t, true);
                    }
                }
                this.elements = newElements;
                this.RecalculateValue();
            }

            internal KPerm2 Duplicate()
            {
                var copy = new KPerm2(value, elements, split, Set, pendingElements);
                copy.RecalculateValue();
                return copy;
            }

            internal void Merge(KPerm2 theOther)
            {
                BigInteger totalValue = this.RecalculateValue();
                for (int t = theOther.split; t < elements.Length; t += 2)
                {
                    if (theOther.elements.Get(t))
                    {
                        elements.Set(t, true);
                        totalValue += Set[t];
                    }
                }
                this.split = 2;
                AddForVerification();
            }
        }

        public class Solver2
        {
            public BigInteger globalKSubsets = new BigInteger(0);

            public HashSet<BigInteger> CurrentRoundL0 = new HashSet<BigInteger>();
            public HashSet<BigInteger> CurrentRoundL1 = new HashSet<BigInteger>();

            public HashSet<BigInteger> TabuSearchL1 = new HashSet<BigInteger>();
            public HashSet<BigInteger> TabuSearchL0 = new HashSet<BigInteger>();

            public List<ulong> S = new List<ulong>();

            public List<ulong> L0 = new List<ulong>();
            public List<ulong> L1 = new List<ulong>();

            public Dictionary<BigInteger, KPerm2> allL0 = new Dictionary<BigInteger, KPerm2>();
            public Dictionary<BigInteger, KPerm2> allL1 = new Dictionary<BigInteger, KPerm2>();

            public List<ulong> allL0TargetValues = new List<ulong>();
            public List<ulong> allL1TargetValues = new List<ulong>();

            public ulong L0TotalSum = 0;
            public ulong L1TotalSum = 0;
            public ulong problemSpace = 0;
            public ulong targetValue = 0;

            public string StepName { get; set; }
            public bool Solve(List<ulong> S, int n, int p, ulong targetValue, int stopAt, int toZero, string name)
            {
                List<ulong> originalS = new List<ulong>(S);
                bool found = false;
                this.StepName = name;
                this.S = S;
                bool spaceExhausted = false;

                //Multiplex mpl = new Multiplex(S, n, p, 2);

                Console.WriteLine($"Solver executing: {S.Count()} elements in the input target {targetValue}.");

                ulong problemSpace = 0;
                S.ForEach(i => problemSpace += i);

                int finalLocation = (int)((targetValue / (double)problemSpace) * 100);

                Console.WriteLine($"Enumerating... ({this.StepName}) for targetValue {this.targetValue}");

                List<KPerm2> input = InitializeSplits();


                for (int t = n - toZero; t < n; t++)
                {
                    S[t] = 0;
                }

                if (input.Count > 0)
                {

                    ulong totalOperations = 0;
                    ulong totalRejected = 0;
                    ulong totalKSubsets = 0;
                    ulong totalLeftSplitOperations = 0;
                    ulong totalRightLeftSplitOperations = 0;
                    ulong wandLeft = 0;


                    ulong lastTotalKSubsets = 0;
                    System.IO.File.AppendAllLines("InputSize.txt", new string[] { "".PadLeft(20, '-') });

                    lastTotalKSubsets = 0;

                    ulong additional = 0;


                    for (int i = 0; i < stopAt; i++)
                    {
                        ulong delayedSoFar = 0;
                        ulong maxSubsetsOnAnySubiteration = 0;


                        Console.WriteLine($"({i + 1}) ".PadRight(40, '-'));
                        List<KPerm2> output = new List<KPerm2>();


                        ulong roundLeftSplitOperations = 0;
                        ulong roundRightSplitOperations = 0;

                        CurrentRoundL0 = new HashSet<BigInteger>();
                        CurrentRoundL1 = new HashSet<BigInteger>();

                        foreach (var currentKPerm in input)
                        {
                            var currentTabuSearch = TabuSearchL0;
                            var TheOtherTabuSearch = TabuSearchL1;
                            var currentSplitList = allL0;
                            var theOtherSplitList = allL1;

                            var currentSplitSum = L0TotalSum;
                            var theOtherSplitSum = L1TotalSum;
                            var currentTargetValues = allL0TargetValues;
                            var theOtherTargetValues = allL1TargetValues;

                            // swith to the other split
                            if (currentKPerm.split == 1)
                            {
                                currentTabuSearch = TabuSearchL1;
                                TheOtherTabuSearch = TabuSearchL0;
                                currentSplitSum = L1TotalSum;
                                theOtherSplitSum = L0TotalSum;
                                currentSplitList = allL1;
                                theOtherSplitList = allL0;
                                currentTargetValues = allL1TargetValues;
                                theOtherTargetValues = allL0TargetValues;
                            }

                            bool expand = true;

                            if (expand)
                            {
                                var iteration = 0;

                                var adjust = toZero;

                                if (toZero != 0)
                                {
                                    adjust = toZero / 2;
                                }


                                for (int pendingElementsIdx = 0; pendingElementsIdx < currentKPerm.pendingElements.Count - adjust && found == false; pendingElementsIdx++)
                                {
                                    if (currentKPerm.split == 0)
                                    {
                                        totalOperations++;
                                    }
                                    else
                                    {
                                        int nop = 0;
                                    }

                                    int kThIdx = currentKPerm.pendingElements[pendingElementsIdx];

                                    ulong kTh = S[kThIdx];
                                    var added = currentKPerm.value + kTh;

                                    bool shouldProcess = true;

                                    if (currentTabuSearch.Contains(added))
                                    {
                                        shouldProcess = false;
                                        if (currentKPerm.split == 0)
                                        {
                                            totalRejected++;
                                        }
                                    } 
                                    if (shouldProcess)
                                    {
                                        currentTabuSearch.Add(added);
                                        currentTabuSearch.Add(currentSplitSum - added);

                                        var newKPerm = new KPerm2(added, currentKPerm.elements, currentKPerm.split, S, currentKPerm.pendingElements.Remove(kThIdx));

                                        newKPerm.elements.Set(kThIdx, true);
                                        newKPerm.value = added;

                                        if (currentSplitList.ContainsKey(added) == false)
                                        {
                                            currentSplitList.Add(added, newKPerm);
                                        }

                                        if (currentSplitList.ContainsKey(currentSplitSum - added) == false)
                                        {
                                            currentSplitList.Add(currentSplitSum - added, newKPerm);
                                        }

                                        if (added != 0)
                                        {
                                            output.Add(newKPerm);
                                        }

                                        totalKSubsets++;
                                        globalKSubsets++;

                                        if (newKPerm.split == 0)
                                        {
                                            lastTotalKSubsets++;
                                            maxSubsetsOnAnySubiteration++;
                                        }

                                        ////////////////////// WANDS
                                        if (true)
                                        {
                                            if ((added) == targetValue || currentSplitSum - added == targetValue)
                                            {
                                                found = true;

                                                if (added != targetValue)
                                                {
                                                    if (currentSplitSum - added == targetValue)
                                                    {
                                                        Console.WriteLine();
                                                        Console.WriteLine("->Found in A'");
                                                        newKPerm.ReverseElements();
                                                    }
                                                }
                                                else
                                                {
                                                    Console.WriteLine();
                                                    Console.WriteLine("->Found in A");
                                                }
                                            }
                                            else
                                            {
                                                BigInteger lookupABAndBPrime = targetValue - added;
                                                if (theOtherSplitList.ContainsKey(lookupABAndBPrime))
                                                {
                                                    var theOther = theOtherSplitList[lookupABAndBPrime].Duplicate();
                                                    var theOtherR = theOtherSplitList[lookupABAndBPrime].Duplicate();
                                                    theOtherR.ReverseElements();

                                                    theOther.Set = originalS;
                                                    theOtherR.Set = originalS;

                                                    if (theOther.value != lookupABAndBPrime)
                                                    {
                                                        Console.WriteLine("\t ");
                                                        Console.WriteLine("\t -> Found in A+B'");
                                                        theOther.ReverseElements();
                                                    }
                                                    else
                                                    {
                                                        Console.WriteLine("\t ");
                                                        Console.WriteLine("\t -> Found in A+B");
                                                    }
                                                    newKPerm = newKPerm.Duplicate();
                                                    newKPerm.Merge(theOther);
                                                    found = true;
                                                }
                                                else
                                                {
                                                    BigInteger lookupAPrimeBAndBPrime = targetValue - (currentSplitSum - added);
                                                    if (theOtherSplitList.ContainsKey(lookupAPrimeBAndBPrime))
                                                    {
                                                        var theOther = theOtherSplitList[lookupAPrimeBAndBPrime];
                                                        var currentReverse = newKPerm.Duplicate();
                                                        theOther.Set = originalS;
                                                        currentReverse.Set = originalS;
                                                        currentReverse.ReverseElements();

                                                        if (theOther.value != lookupAPrimeBAndBPrime)
                                                        {
                                                            Console.WriteLine("\t ");
                                                            Console.WriteLine("\t -> Found in A'-B'");
                                                            theOther.ReverseElements();
                                                            theOther.Merge(currentReverse);
                                                        }
                                                        else
                                                        {
                                                            theOther.Merge(currentReverse);
                                                            Console.WriteLine("\t ");
                                                            Console.WriteLine("\t -> Found in A'-B");
                                                        }
                                                        newKPerm = theOther;

                                                        found = true;
                                                    }
                                                }
                                            }

                                            if (found)
                                            {
                                                newKPerm.Set = originalS;
                                                newKPerm.AddForVerification();
                                                // we good?
                                                if (targetValue == newKPerm.value)
                                                {
                                                    Console.WriteLine("\n\t-> found subset, validation is OK. " + targetValue + " == " + newKPerm.AddForVerification());
                                                    Console.WriteLine("\n\t-> subset is: " + String.Join(", ", newKPerm.ElementsList()));
                                                }
                                                else
                                                {
                                                    Console.WriteLine("\n\t-> found subset VALIDATION IS WRONG " + targetValue + "==" + newKPerm.AddForVerification());
                                                    Console.WriteLine("\n\t-> found subset VALIDATION IS WRONG " + targetValue + "==" + newKPerm.AddForVerification());
                                                    Console.WriteLine("\n\t-> found subset VALIDATION IS WRONG " + targetValue + "==" + newKPerm.AddForVerification());
                                                    Console.WriteLine("\n\t-> found subset VALIDATION IS WRONG " + targetValue + "==" + newKPerm.AddForVerification());
                                                }

                                                Console.WriteLine(String.Concat("\t", newKPerm.ToString()));
                                                Console.WriteLine();

                                                System.IO.File.WriteAllLines("result.set", newKPerm.ElementsList());
                                                Console.WriteLine($"Operations: {totalOperations}");

                                                found = true;
                                            }
                                        }


                                        if (newKPerm.split == 0)
                                        {
                                            roundLeftSplitOperations++;
                                            totalLeftSplitOperations++;
                                        }
                                        else
                                        {
                                            totalRightLeftSplitOperations++;
                                            roundRightSplitOperations++;
                                        }
                                    }
                                    iteration++;
                                }
                                currentKPerm.pendingElements = null;
                            }

                            if (found)
                            {
                                break;
                            }

                            if (totalKSubsets == System.Math.Pow(2, n / 2) - 2) // ignore
                            {
                                spaceExhausted = true;
                                break;
                            }
                        }

                        Console.WriteLine($"({i + 1} -> Operations: {totalOperations} | Additional: {additional} | Rejected: {totalRejected} ({roundLeftSplitOperations.ToString("N0")}/{roundRightSplitOperations.ToString("N0")}) (Ops/KSubsets: {(totalOperations / (double)totalKSubsets).ToString("N2")}) | kSubsets: {output.Count.ToString("N0")} | del {delayedSoFar.ToString("N0")}");

                        input = output;


                        System.IO.File.AppendAllLines("ksubsetroundperline.txt", new string[] { $"{maxSubsetsOnAnySubiteration}" });


                        ulong acum = 0;

                        if (found || output.Count == 0 || spaceExhausted)
                        {
                            break;
                        }


                    }

                    System.IO.File.AppendAllLines("ksubsetround.txt", new string[] { $"{lastTotalKSubsets}" });

                    // uncomment to save both split lists to disk
                    // StringBuilder sb = new StringBuilder();
                    // var allL0List = allL0.Select(i => i.Value.value).ToList();
                    // foreach (var k in allL0List)
                    // {
                    //    sb.AppendLine(k.ToString());
                    // }

                    // System.IO.File.AppendAllText($"L0-{StepName}.set", sb.ToString());

                    // sb.Clear();
                    // var allL1List = allL1.Select(i => i.Value.value).ToList();
                    // foreach (var k in allL1List)
                    // {
                    //    sb.AppendLine(k.ToString());
                    // }

                    //System.IO.File.AppendAllText($"L1-{StepName}.set", sb.ToString());


                    double midmlCount = System.Math.Pow(2.0, S.Count() / 2);
                    Console.WriteLine("---------------------------------------------------------------");
                    Console.WriteLine("---------------------------------------------------------------");
                    Console.WriteLine($"Total Operations: {totalOperations.ToString("N0")} | AvgOps per KSubset: {totalOperations / (double)totalKSubsets})");
                    Console.WriteLine("---------------------------------------------------------------");
                    Console.WriteLine($"kSubsets Total: {(totalKSubsets).ToString("N0")}  out of {midmlCount.ToString("N0")} ({(((totalOperations / 2) / midmlCount) * 100).ToString("N0")} %) | totalLeft: {totalLeftSplitOperations.ToString("N0")} | totalRight: {totalRightLeftSplitOperations.ToString("N0")} | Delayed: 0");

                    if (!found)
                    {
                        Console.WriteLine("---------------------------------------------------------------" + targetValue);
                        Console.WriteLine("No subset found adding up to " + targetValue.ToString("N0"));
                    }

                    System.IO.File.AppendAllLines("counts.txt", new string[] { $"{n}/{p} {totalLeftSplitOperations.ToString("N0")} {totalOperations.ToString("N0")}" });
                }


                return found;
            }

            private List<KPerm2> InitializeSplits()
            {
                List<KPerm2> initialInput = new List<KPerm2>();


                L0 = new List<ulong>();
                L1 = new List<ulong>();

                L0TotalSum = 0;
                L1TotalSum = 0;

                for (int t = 0; t < S.Count; t++)
                {
                    ulong value = S[t];


                    problemSpace += value;

                    if (t % 2 == 0)
                    {
                        L0.Add(value);
                        L0TotalSum += value;
                    }
                    else
                    {
                        L1.Add(value);
                        L1TotalSum += value;
                    }
                }

                if (L0TotalSum == targetValue)
                {
                    Console.WriteLine("Target Value = L0TotalSum");
                    return new List<KPerm2>();
                }

                if (L1TotalSum == targetValue)
                {
                    Console.WriteLine("Target Value = L1TotalSum");
                    return new List<KPerm2>();
                }
                List<int> split0StartIndexes = new List<int>();
                List<int> split1StartIndexes = new List<int>();
                for (int o = 0; o < S.Count; o += 2)
                {
                    split0StartIndexes.Add(o);
                    split1StartIndexes.Add(o + 1);

                }
                initialInput.Add(new KPerm2(0, new BitArray(S.Count), 0, S, split0StartIndexes.ToImmutableList<int>()));
                initialInput.Add(new KPerm2(0, new BitArray(S.Count), 1, S, split1StartIndexes.ToImmutableList<int>()));


                return initialInput;
            }

        }

        private static void InitializeWithArgs(string[] args, int n, int p, int targetLocation)
        {
            bool automatic = true;

            if (args.Length == 5)
            {
                if (args[3].ToLower() == "repeat")
                {
                    automatic = false;
                    targetValue = ulong.Parse(args[4]);
                    if (System.IO.File.Exists("last.set"))
                    {
                        string[] numbers = System.IO.File.ReadAllLines("last.set");
                        foreach (var number in numbers)
                        {
                            ulong item = ulong.Parse(number);
                            S.Add(item);
                            problemSpace += item;
                        }
                    }
                }
            }

            if (automatic)
            {
                // generate tight random number in the upper range of p to make them really hard.
                ulong limit = (ulong)System.Math.Pow(2, p - 1) + (ulong)((System.Math.Pow(2, p - 1) / 4) * 3);
                for (int t = 0; t < n; t++)
                {
                    ulong item = Get64BitRandom(1, (ulong)System.Math.Pow(2, p));
                    if (item < limit)
                    {
                        t--;
                    }
                    else
                    {
                        if (S.Contains(item))
                        {
                            t--;
                        }
                        else
                        {
                            S.Add(item);

                            problemSpace += item;
                        }
                    }
                }
                int solutionTerms = 0;
                // build up a target value, do not allow repetition, try to get as near as possible as the targetLocation % requested
                List<ulong> targetUsed = new List<ulong>();
                while ((int)((targetValue / (double)problemSpace) * 100) < (double)targetLocation)
                {
                    int i = rnd.Next(n);
                    if (targetUsed.Contains(S[i]) == false)
                    {
                        solutionTerms++;
                        targetUsed.Add(S[i]);
                        targetValue += S [i];
                    }
                }
                S.Sort();

                Console.WriteLine($"Solution is composed by {solutionTerms} elements.");

                // Save the random input instance to a file
                List<string> numbers = new List<string>();
                foreach (ulong s in S)
                {
                    numbers.Add(s.ToString());
                }

                System.IO.File.WriteAllLines("last.set", numbers.ToArray());


                // Save the Solution to a file
                List<string> number2 = new List<string>();
                targetUsed.Sort();

                foreach (ulong s in targetUsed)
                {
                    number2.Add(s.ToString());
                }

                System.IO.File.WriteAllLines("solution.set", number2.ToArray());

                // Save the random input instance to a file
                numbers = new List<string>();
                foreach (ulong s in S)
                {
                    var tow = String.Join(" | ", Split(Convert.ToString((long)s, 2), 3).ToArray());

                    numbers.Add(tow);
                }

                var tow2 = String.Join(" | ", Split(Convert.ToString((long)targetValue, 2), 3).ToArray());
                numbers.Add("-----------------------------");
                numbers.Add(tow2);
                numbers.Add("-----------------------------");

                System.IO.File.WriteAllLines("lastb.set", numbers.ToArray());



                // Save the random input instance to a file
                numbers = new List<string>();
                foreach (ulong s in targetUsed)
                {
                    var tow = String.Join(" | ", Split(Convert.ToString((long)s, 2), 3).ToArray());

                    numbers.Add(tow);
                }

                System.IO.File.AppendAllLines("lastb.set", numbers.ToArray());
            }
        }

        static IEnumerable<string> Split(string str, int chunkSize)
        {
            return Enumerable.Range(0, str.Length / chunkSize)
                .Select(i => str.Substring(i * chunkSize, chunkSize));
        }

        static ulong Get64BitRandom(ulong minValue, ulong maxValue)
        {
            // Get a random array of 8 bytes. 
            // As an option, you could also use the cryptography namespace stuff to generate a random byte[8]
            byte[] buffer = new byte[sizeof(ulong)];
            rnd.NextBytes(buffer);
            return BitConverter.ToUInt64(buffer, 0) % (maxValue - minValue + 1) + minValue;
        }
    }

    // The Solver :)

    public class Pool<T> where T : new()
    {
        private Stack<T> _items = new Stack<T>();
        private object _sync = new object();

        public T Get()
        {
            lock (_sync)
            {
                if (_items.Count == 0)
                {
                    return new T();
                }
                else
                {
                    return _items.Pop();
                }
            }
        }

        public void Free(T item)
        {
            lock (_sync)
            {
                _items.Push(item);
            }
        }



    }
}
