using LinearAlgebra
using SparseArrays
using Plots

struct SparseMatrixCSR{T} <: AbstractMatrix{T}
    rowPtr::Vector{Int64}
    colInd::Vector{Int64}
    values::Vector{T}

    function SparseMatrixCSR{T}(rowIdx::Vector{Int64}, colIdx::Vector{Int64}, vals::Vector{T}) where T
        n = maximum(rowIdx)
        m = maximum(colIdx)
        nnz = length(vals)
        rowPtr = zeros(Int64, n + 1)
        for r in rowIdx
            rowPtr[r + 1] += 1
        end
        for i = 2:length(rowPtr)
            rowPtr[i] += rowPtr[i - 1]
        end
        colInd = Vector{Int64}(undef, nnz)
        values = Vector{T}(undef, nnz)

        for k in 1:nnz
            row = rowIdx[k]
            dest = rowPtr[row] + 1
            rowPtr[row] = dest
            colInd[dest] = colIdx[k]
            values[dest] = vals[k]
        end
        for row = length(rowPtr)-1:-1:1
            rowPtr[row+1] = rowPtr[row]
        end
        rowPtr[1] = 1

        new{T}(rowPtr, colInd, values)
    end
end

Base.size(A::SparseMatrixCSR) = (length(A.rowPtr) - 1, maximum(A.colInd))

function Base.getindex(A::SparseMatrixCSR{T}, i::Int, j::Int) where T
    row_start = A.rowPtr[i]
    row_end = A.rowPtr[i + 1] - 1
    for idx in row_start:row_end
        if A.colInd[idx] == j
            return A.values[idx]
        end
    end
    return zero(T)
end

function LinearAlgebra.mul!(out::AbstractVector{T}, A::SparseMatrixCSR{T}, x::AbstractVector{T}) where T
    fill!(out, zero(T))
    for i in 1:size(A, 1)
        for j in A.rowPtr[i]:(A.rowPtr[i + 1] - 1)
            out[i] += A.values[j] * x[A.colInd[j]]
        end
    end
    return out
end

function iterate_and_plot(A::SparseMatrixCSR{T}, b::AbstractVector{T}, u::AbstractVector{T}, a::T; tol::T = 1e-3, target_norm::T = 7.11) where T
    iterations = 100
    r = b - A * u
    norms = []
    out = similar(u)  # Preallocate space for A * u

    while true
        norm_r = norm(r)
        push!(norms, norm_r)
        if norm_r < target_norm
            break
        end

        mul!(out, A, u)  # Efficiently compute A * u and store the result in out
        r = b - out
        u .+= a .* r     # Perform the iteration step

        if iterations > 1e4  # Limit to prevent infinite loop
            println("Iteration limit reached without convergence.")
            break
        end

        if any(isnan.(u)) || any(isinf.(u))  # Check for numerical issues
            println("Numerical instability detected.")
            break
        end

        iterations += 1
    end

    p = plot(norms, title = "Norm of r over Iterations", xlabel = "Iteration", ylabel = "Norm of r", legend = false)
    return u, iterations, norm(r), p
end



function main()
    rowIdx = [1, 2, 3, 3]
    colIdx = [1, 2, 3, 1]
    vals = [4.0, 5.0, 6.0, 7.0]

    A = SparseMatrixCSR{Float64}(rowIdx, colIdx, vals)
    b = [1.0, 2.0, 3.0]
    u = zeros(Float64, 3)

    final_u, num_iterations, final_norm, norms = iterate_and_plot(A, b, u, 1.0)
    println("Final u: ", final_u)
    println("Number of iterations: ", num_iterations)
    println("Final norm of r: ", final_norm)

    display(plot!()) 
end

main()
