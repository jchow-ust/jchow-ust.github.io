install.packages("maxLik")
library("maxLik")
mu <- -1.6
sigma <- 2
x <- runif(50, min=mu-sigma*(3^0.5), max=mu+sigma*(3^0.5))

llik = function(par)
{
  mu_est=par[1]
  sigma_est=par[2]
  n=length(x)
  indicator=1
  if (mu_est-sigma_est*(3^0.5) > min(x)){
    indicator=0
  }
  if (mu_est+sigma_est*(3^0.5) < max(x)){
    indicator=0
  }
  l1=-n*log(2*sigma_est*(3^0.5))*indicator
  return(l1)
}
mle_unif = maxLik(loglik=llik, start=c(mu=0, sigma=1), method="NR")
summary(mle_unif)
