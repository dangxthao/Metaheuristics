function best_point = probabilistic_restart(usedPoints,xmin,xrange,nPoints)
    Ndim=size(usedPoints,1);
    best_prob=Inf;
    for k=1:nPoints
        % cast a random point somewhere in the allowed range     
        random_point=xmin+xrange.*rand(Ndim,1);
        random_prob = gauss(random_point, usedPoints, xrange);

        if random_prob < best_prob % minimise probability
            best_point = random_point;
            best_prob  = random_prob;
        end
    end
end

function prob = gauss(x,points,xrange)
    glp = 0.01; % Gaussian length parameter (see [Luersen2004, 2.1 Probabilistic restart])
    [Ndim, Npts] = size(points);
    sigma = diag(glp*xrange.^2);
    sigmainv = diag(1./diag(sigma));
    prob = 0;
    for k=1:Npts
        mu = points(:,k);
        if mu == zeros(Ndim,1), break; end
        prob = prob + exp(-.5*(x-mu)'*sigmainv*(x-mu))/sqrt((2*pi)^Ndim*det(sigma));
    end
end

