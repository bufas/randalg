(ns find.core
  (:require [clojure.tools.cli :refer [cli]])
  (:gen-class))

;; Shuffles a list of random numbers
;; [0, ... , n-1]
(defn generate-random-numbers [n]
  (shuffle (range n)))

;; Picks a random element in a list
(defn pick-random-element [list]
  (let [random-integer (rand-int (count list))]
    (nth list random-integer)))

;; Divides list into L1 and L2 
;; if |L1|=k-1 we have found the kth least number
;; if |L1|>k-1 then the kth least number must be in L1 (recurse)
;; if |L1|<k-1 then the kth least number must be in L2 
;; (recurse and subtract |L1|.
(defn find-algorithm [list k s]
  (let [random-element (pick-random-element list)
        partition (group-by #(> random-element %) (remove #(= random-element %) list))
        l1 (partition true)
        l2 (partition false)]
    (cond 
     (= (count l1) (dec k))
     s
     (> (count l1) (dec k))
     (find-algorithm l1 k (inc s))
     :else
     (find-algorithm l2 (- (dec k) (count l1)) (inc s)))))

(defn -main [& args]
  (if (not (= (count args) 2))
    (println "You should call the jar with two arguments: n and k")
    (let [[n k] (map #(Integer/parseInt %) args)
          height (find-algorithm (generate-random-numbers n) k 0)]
      (println "The height of the generated search tree is" height))))












