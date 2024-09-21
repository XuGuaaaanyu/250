d = linspace(1e-3,1e-2,50);
P = linspace(0.5,2,50); 

[p,D] = meshgrid(P,d);
sigma0 = -94.5+27.4.* p./(D.^2);
sigma = 4500000./sigma0;


% Plotting
figure;
surf(p,D,sigma0);
colorbar;
ylabel("Thickness of bottom board, d [m]");
xlabel("Mass of guide track, m_g [kg]");
title("Maximum normal stress , σ_{max}");
figure;
contour(D,p,sigma,30);
colorbar;
xlabel("Thickness of bottom board, d [m]");
ylabel("Mass of guide track, m_g [kg]");
title("Safety factor, σ_f/σ_{max}");