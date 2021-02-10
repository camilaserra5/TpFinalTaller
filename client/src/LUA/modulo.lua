--PREGUNTAR: EL JUGADOR LUA, ESTA BIEN SI TIENE BALAS INFINITAS Y QUE NO PUEDA AGARRAR COSAS PARA CURARSE?
--COMO HARIA PARA 'DISPARAR'?????
--SE PUEDE QUEDAR QUIETO MIENTRAS DISPARA?? O SI O SI TIENE QUE HACER MOVIMIENTO MIENTRA ATACA?

-- macro Variable
next_position = {
    [-1] = "A", -- IZQUIERDA
    [0] = "W", -- ADELANTE
    [1] = "D", -- DERECHA
    [2] = "S" -- RETROCEDER
}

--Funcion que verifica si puede avanzar
--Nota: todo lo que sea distinto a 'false' 'nil' es tomado como true;
function proximo_movimiento(pos_x, pos_y)
    if (mapa[pos_x+1][pos_y]==0) then
        return next_position[1]
    end
    if (mapa[pos_x-1][pos_y]==0) then
        return next_position[-1]
    end
    if (mapa[pos_x][pos_y=1]==0) then
        return next_position[0]
    end
    if (mapa[pos_x][pos_y-1]==0) then
        return next_position[2]
    end
end

function moverse(pos_x,pos_y)
    local siguiente_mov = proximo_movimiento(pos_x,pos_x)
