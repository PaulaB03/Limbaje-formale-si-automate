# 📎Finite Automata to Regex

### Table of Contents

- [Step1](#Step1)
- [Step2](#Step2)
- [Step3](#Step3)
- [Step4](#Step4)
- [Exemples](#Exemples)

##  Step1 

- If the state *p* has more transitions to the state *q*, then we replace those transitions with a regular expression

```sh
Exemple:     a,b,c                        a|b|c
      ... p -------> q ...   ~~~>  ... p -------> q ...
```

## Step2

- If the initial state is final or there are transitions to the initial state, then we add a new state that will be initial and will have a λ transition to the old initial state</li></br>

```sh 
Exemple:
               a                         λ       a
       --> 0 <===> 1 ...   ~~>    --> 2 ---> 0 <===> 1 ...
               b                                 b
```
## Step3

- If there are more finals states or there are transitions from the final state, then we add a new state that will be final and all the old final states will have a λ transition to the new final state</li></br>

```sh 
Exemple:
               a                          λ      a
       <-- 0 <===> 1 ...   ~~>    <-- 2 <--- 0 <===> 1 ...
               b                                 b
```

## Step4

- We eliminate all the states exept the initial and the final state with the following ecuation:

```sh 
            tr(p,s)                        
          p -------> s  
           \         ^                        tr(p,s)|tr(p,q)tr(q,q)*tr(q,s)
    tr(p,q) \       /            ~~~>     p --------------------------------> s
             \     / tr(q,s)
              v   /
                q
               | ↑ tr(q,q)
                ‾
```
We ant to eliminate the state *q* and there are the transitions tr(p,q), tr(q,s) and the loop tr(q,q)
Then we will have a new transition from the state *p* to the state *s* : the union between the direct transition tr(p,s) or Ø if there is no thansition and the concatenation
of the transactions tr(p,q), tr(q,q)* and tr(q,s)

## Exemples

- Exemple 1
<img src="https://github.com/PaulaB03/Limbaje-formale-si-automate/blob/master/Proiect2/Exemples/Exemple1.jpg">

- Exemple 2
<img src="https://github.com/PaulaB03/Limbaje-formale-si-automate/blob/master/Proiect2/Exemples/Exemple2.jpg">
