Brainfuck.NET Compilator (c), Syschikov Andey
andreysch@peterlink.ru
www.jabb-sch.narod.ru/bf/

(0) Contents
    (1) Requiremets
    (2) How does it works
    (3) Optimization
    (4) Extension
    (5) Parametrization
    (6) Data input
    (7) Data output
    (8) Integration

(1) Requiremets
Working computer, Microsoft.NET Framework v1.0 or higher
Will it work on PocketPC? No! (because of CSharpCodeProvider class)

(2) How does it works
bfdotnet.exe takes a BF source code and produces a .NET PE-file (console)
Actually, I didn't wrote a compilator. This is BF to CSharp translator, which
later compiles CSharp code using CSharpCodeProvider class. But from outside
it looks as a compiler.

(3) Optimization
There is some optimization on BF to CSharp translation,
instead of tranlating ">>>" to
    ind++;
    ind++;
    ind++;
  it writes 
    ind += 3; (where Inc(..) is some method)
    or "+++" to arr[ind] += 3; (in one line!)
Totally, compiled files work rather fast, surely faster then on BF interpreters

(4) Extension (-ext in command line)
bfdotnet.exe understands compilation directives. The synthax is "Oxx",
where O is any of the < > + - BF operators, and xx is a number.
Compiler understands this as O times xx. F.e. "+3" is same as "+++"
See, this extension doesn't modify BF itself, but its usage isnt obligatory
NB: Directive is not compatible with [ ] , . operators!!
NB: Be sure not to use digits as a comments with -ext! They become ambigous! 

(5) Parametrization (-p in command line)
bfdotnet.exe is capable of making compiled BF programms understand command line
parametr. Synthax is "bfdotnet.exe (.) -e exmpl.exe -p" then 
"exmpl.exe xxx" where xxx is any string. It will be added to input buffer
on programm start up. It means, when you used "," it will (first read
first char of line then second and so one. once string is finished, on next
"," call user will be asked to enter data. See (6) Data input

(6) Data input
When "," is called, user may enter any string to pogramm (finished with Enter)
This string will be placed in buffer and first char will be immediately read
(Remember, "," was called). Last char in string has always code 10, meaning
EOL (End of line) Even when string is inputted as commandline parameter.

(7) Data output
Data output is standart ("."). To start a new line pass a 10 code

(8) Integration
You may integate this compiler into any .NET application.
In bfdotnet.dll is a BFCompiler class implemented.
To use it, follow this steps:
1) Add a reference to bfdotnet.dll
2) Link a BFdotNET namespace (optional)
3) Use static class BFCompiler or (if you skiped step 2) BFdotNET.BFCompiler
4) To translate BF code to CSharp code use BFCompiler.BFtoCS method:
   static public string BFtoCS(string code, bool warn, bool ext, bool par)
      code - code in BF
      warn - enable translator warnings
      ext - translator directives (Oxx)
      par - add parametrization
5) To compile BF code use BFCompiler.Compile method:
   static public void Compile(string[] args)
      args - array of strings with compilation attributes. pass them as they
             are passed to Main(string[] args) from command line