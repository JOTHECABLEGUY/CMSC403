(defun myList() "function to build a list"
	(list 4 (list 7 22) "art" (list "math" (list 8) 99) 100) 			;use list function to make elements lists
)

(defun leapYear(&optional (year 1800) (leapList (list))) "function to build list of leap years from 1800 to now"
	(if(> year 2021)   								;return when we reach 2021
		(return-from leapYear leapList) 					;return the whole list
		()
	)
	(if(zerop(mod year 4)) 									;divisible by 4?
		(if(zerop(mod year 100)) 							;divisible by 100?
			(if(zerop(mod year 400)) 						;divisible by 400?
				(leapYear (+ year 4) (append leapList (list year))) 		;if divisible by 400, then it is a leap year, so add it to result list	
				(leapYear (+ year 4) leapList) 					;if not divisible by 400, then don't add it to the result and call leapYear again
			)	
			(leapYear (+ year 4) (append leapList (list year))) 		;if divisible by 4 and not 100 add it to result list
		)
		()
	)
)

(defun union-(&optional (list1 (list)) (list2 (list))) "function that returns the union of 2 lists"
	(if(null list2) 
		(return-from union- list1) 						;if first list is null, return the second list
		()
	)
	(if(null list1) 									;base case, list1 gets smaller with each recursive call, so it will eventually be null
		(return-from union- list2)						;if second list is null, return the first list
		()
	)
	(if(null(member (car list1) list2)) 					;member returns a list, so if it is null, then the first element of list1 is not in list2
		(union- (cdr list1) (append list2 (list (car list1)))) 		;it is fine to the first element of list1 to list2 without concern for duplicates
		(union- (cdr list1) list2) 							;if there is a duplicate, skip it
	)
)

(defun avg (aList &optional (result 0) (size 0) ) "function that calculates the average of a given list"
	(if(null aList) 								;base case, where we format and return the average
		(if(= result 0)
			(return-from avg NIL) 					;if given an empty list, result will be 0, and so we return NIL
			(return-from avg (/ result size)) 				;else we return the sum/size
		)	
		()
	)
	(avg (cdr aList) (+ result (car aList)) (+ size 1)) 		; recursive call to add the current element to growing result and add 1 to size
)

(defun isType(dataType) "function that returns a function that checks datatype of a single parameter with the given datatype"
	(lambda (x) (typep dataType x)) 			;returns a lambda that will return true if the single parameter x matches the datatype given to isType
)

(defun taxCalculator(limit rate values &optional (result (list))) "function that takes a list and applies tax rate if the element exceeds the limit"
	(if(null values) 						;base case, when all values have been visited 
		(return-from taxCalculator result) 		;returns the list of updated values
		()
	)
	(let ((v (car values))) 										;set a local variable to first element in values, which makes code look cleaner
		(if(> v limit) 
			(taxCalculator limit rate (cdr values) (append result (list (* v rate))) ) 			;if element exceeds limit, apply discount and continue iterating
			(taxCalculator limit rate (cdr values) (append result (list v)) ) 				;if not, just add the element to the result and interate once more
		)
	)	
)
(defun clean (aFunc aList &optional (result (list)) ) "function that applies the given function to all elements in the given list"
	(if(null aList) 									;base case returns the result list when all values in aList have been used up
		(return-from clean result)
		()
	)
	(if(typep (car aList) 'cons) 									;if the current element is a list, step into the list
		(if(funcall aFunc (car(car aList))) 							;if the first element of the sublist can be applied
			(clean aFunc (cdr aList) (append result (list (car(car aList)))))  	;call clean on the next element in the sublist
			(clean aFunc (cdr aList) result) 							;else iterate 
		)
		()
	)
	(if(funcall aFunc (car aList)) 
		(clean aFunc (cdr aList) (append result (cons (car aList) ()))) 			;call clean on the rest of input list after appending the current element if the function can be applied to it
		(clean aFunc (cdr aList) result)
	)
)

(defmacro threewaybranch (x y z) "macro that takes 3 lists and executes the first branch to be evaluated to true"
	(if (eval(car x))
		`(if ,(car x) (progn ,@(cdr x))) 					;if the x condition is true, set up an execution of the statements in the x branch
		(if (eval(car y))
			`(if ,(car y) (progn ,@(cdr y)))  				;if the y condition is true, set up an execution of the statements in the y branch
			(if (eval(car z))
				`(if ,(car z) (progn ,@(cdr z))) 			;if the z condition is true, set up an execution of the statements in the z branch
				() 								;if no conditions are true, return NIL
			)
		)
	)
)


	
	
	

	