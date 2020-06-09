cutoff = 128;

tmp = find(A>cutoff);
A(:,:,:) = 0;
A(tmp)   = 255;

clear cutoff tmp;
