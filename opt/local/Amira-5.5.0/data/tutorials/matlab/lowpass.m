cutoff=0.05;

[N,M]=size(A); % retrieve image size

result=fftshift(fft2(A)); % Fourier transform

for i=1:N 
    for j=1:M
        r2=(i-round(N/2))^2+(j-round(N/2))^2; 
        if (r2>round((N*cutoff)^2)) result(i,j)=0; end; 
    end; 
end; 
     
result=real(ifft2(fftshift(result))); % inverse Fourier transform

clear N M i j cutoff r2;
