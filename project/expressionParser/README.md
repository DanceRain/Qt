# 程序说明

该程序是一个表达式解释器。我使用C++而并非Qt将其实现了一遍，希望能够加深我对该程序的理解并能举一反三。

治大国，若烹小鲜。一个复杂的问题，将其拆分成一个个小问题，然后逐一解决就能得到答案。该程序很好的说明了这一点。





在开始表达式解释器的学习之前。我们首先弄懂三个概念：**表达式**、**项**、**因子**。

我们将表达式的组成元素称为项，而将项的组成元素称为因子。

所以，形如 （a + b） * c 这样的称之为表达式，在  （a + b） * c 中形如 （a +b）和c的我们称之为项， 而在项（a+b）中，a、b则是该项的因子。而我们又知道，一个因子有可能也是一个表达式，只不过相对于项来说，它目前是一个因子罢了。这种层层嵌套的关系，我们可以利用递归来解决（*我们可以想象一个大型公司，总经理负责其日常运营，而大型公司又有许多子公司，这些子公司又有总经理。其结构只不过比其母公司更少一层罢了*）。



这样，问题的界限就弄清楚了，我们现在只需要知道如何解析表达式，而解析表达式只需要知道如何才能解析项，项也只需要知道如何解析因子。于是就有了如下程序:

```c++
double anaExpression(const string& exp, string::iterator& pos)
{
	double result = anaTerm(exp, pos);
	while (pos != exp.end())
	{
        ...
		double term = anaTerm(exp, pos);
        ...
	}
	return result;
}
```

```c++
 double anaTerm(const string& exp, string::iterator& pos)
{
	double result = anaFactor(exp, pos);
	while (pos != exp.end())
	{
        ...
		double term = anaFactor(exp, pos);
        ...
    }
	return result;
}
```

```c++

double anaFactor(const string& exp, string::iterator& pos)
{
    ...
	if (*pos == '(')
	{
        ...
		result = anaExpression(exp, pos);
        ...
	}
	...
	return result;
}

```

如何理解上述程序，其实很简单。举例说明例如 **2\*3+5\*2*4+7** 这个式子，我们只需要将其看成 

**(2\*3)+（（5\*2*4）+7) **即可以看见，任何式子（除了单项式）其实都是由两部分组成的，先解析第一部分，再解析第二部分，第一部分又拥有它自己的部分一、部分二，第二部分也是如此。

因此，根据此思路，我们就完成了解释器的分析。具体程序请看源文件。

