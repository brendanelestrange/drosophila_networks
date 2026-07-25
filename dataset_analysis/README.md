### Simple analysis of the types in the data. 

We can use the analysis in this folder to see how we might break down this data into subgraphs. We can make a more robust understanding of the relationship between different regions of the brain if we do this.

You may ask, "if you're using python for quick CSV analysis why don't you just use it for the actual algorithm implementation. It'd be so much easier!" My answer to that is that because of how particular this kind of data is and what we want to extract from it, it is necessary to have a custom implementation of cycle searching algorithms to quickly find the most accurate results for cycles in the data.

Dependencies:
```zsh
pandas
```