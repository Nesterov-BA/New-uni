    k1X = f(startX,           startY);
    k1Y = g(startX,           startY);
    k2X = f(startX + h * a10*k1X,  startY + h *  a10*k1Y);
    k2Y = g(startX + h * a10*k1X,  startY + h *  a10*k1Y);
    k3X = f(startX + h * (a20*k1X + a21*k2X),  startY + h * (a20*k1Y + a21*k2Y));
    k3Y = g(startX + h * (a20*k1X + a21*k2X),  startY + h * (a20*k1Y + a21*k2Y));
    double k1 = h*(a30*k1X + a31*k2X + a32*k3X);
    double k2 = h*(a30*k1Y + a31*k2Y + a32*k3Y);
    k4X = f(startX + k1,  startY +  k2);
    k4Y = g(startX + k1,  startY +  k2);