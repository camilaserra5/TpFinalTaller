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
function proximo_movimiento(mapa, pos_x, pos_y)
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

--Revisa en un rango si hay enemigos en el mapa  /PREGUNTA: EL MAPA LO TIENE QUE RECIBIR LAS FUNCIONES O PUEDE AGARRARLA COMO ALGO TIPO EXTERN?
--los jugadores aparecen con numeros mayores o iguales a 100
function posicion_enemigo_cerca(mapa, pos_x, pos_y)
    for i = pos_x - 10, i = 10, 1 do
        for j = pos_y - 10, j + 10, 1 do
            if (mapa[i][j] >= 100) then
                return {posicionX = i, posicionY = j}--true --puede devolver tambien la posicion?
            end
        end
    end
    return nil--false
end

-- Teniendo ya la posicion del enemigo, el jugador lua se tiene que acercar a el
-- siempre en posiciones validas
function avanzar_hacia_enemigo(posicion_enemigo, pos_x, pos_y)
    if (posicion_enemigo.posicionX > pos_x) then
        if (posicion_enemigo.posicionY > pos_y) then
            --avanzar hacia adelante y a la derecha, pero tengo que chequear que pueda avanzar porque se tiene que mover
            -- siempre en posiciones validas
        else
            -- avanzo a la derecha y hacia atras
            --CHEQUEO SI PUEDO
        end
    else
        if (posicion_enemigo.posicionY > pos_y) then
            --avanzar hacia adelante y a la izquierda, pero tengo que chequear que pueda avanzar porque se tiene que mover
            -- siempre en posiciones validas
        else
            -- avanzo a la izquierda y hacia atras
            --CHEQUEO SI PUEDO
        end
    end
end

function moverse(mapa, pos_x, pos_y)
    local siguiente_mov = proximo_movimiento(mapa, pos_x, pos_y)
    local posicion_enemigo = posicion_enemigo_cerca(mapa, pos_x, pos_y)
    if (posicion_enemigo) then
        return avanzar_hacia_enemigo(posicion_enemigo, pos_x, pos_y)
    end
    return siguiente_mov
end

function disparar_al_enemigo()
--como enviaria el danio que hace? puede tener siempre una pistola? como se comunicaria con las cosas de common?
end