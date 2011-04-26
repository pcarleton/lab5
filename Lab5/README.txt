fix double letter tiles getting doubled and counted twice

To do:
-----
Fix so special tile bonuses don't get printed on 1 letter cross checks
i.e. 

	 P
	 O
	SPECIAL
	
If I is a double letter score, it should get printed when checking "SPECIAL"
but not when it checks vertically and no word is formed.

Finish implementing double/triple word scores

Implement Virtual Player
------------------------
Use word collection to iterate over possible words and possible play locations
-NOTE: My word collection class got points off, we may want to replace it with a different one

Things to consider: There are a ton of possible play locations.
Should we try to use our suggesting stuff from lab 4 to make it easier?