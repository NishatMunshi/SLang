func fibonacci : (n) := {
    if(n) {
        if(n-1) {
            ret fibonacci(n-1) + fibonacci(n-2).
        } ret 1.
    } ret 0.
}

func enter : () := {
    ret fibonacci(9).
}