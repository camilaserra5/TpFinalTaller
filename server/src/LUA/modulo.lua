--PREGUNTA: SE PUEDE QUEDAR QUIETO MIENTRAS DISPARA?? O SI O SI TIENE QUE HACER MOVIMIENTO MIENTRA ATACA?
-- EN ESE CSAO COMO SERIA PORQUE SOLO PUEDE DEVOLVER UN CARACTER PARA QUE AFUERA SE GENERE UN COMANDO

-- macro Variable
next_position = {
    [-1] = "a", -- IZQUIERDA
    [0] = "w", -- ADELANTE
    [1] = "d", -- DERECHA
    [2] = "s" -- RETROCEDER
}

--Funcion que verifica si puede avanzar
--Nota: to do lo que sea distinto a 'false' 'nil' es tomado como true;
function proximo_movimiento(pos_x, pos_y)
    if (#mapa[pos_x + 1][pos_y] == 0) then
        return next_position[1]
    end
    if (#mapa[pos_x - 1][pos_y] == 0) then
        return next_position[-1]
    end
    if (#mapa[pos_x][pos_y + 1] == 0) then
        return next_position[0]
    end
    if (#mapa[pos_x][pos_y - 1] == 0) then
        return next_position[2]
    end
end

--Revisa en un rango si hay enemigos en el mapa
--los jugadores aparecen con numeros mayores o iguales a 100
function posicion_enemigo_cerca(pos_x, pos_y)
    local rango = 3
    if(pos_x - rango < 1 or pos_y - rango < 1) then
    rango = 1
    end
    for i = pos_x - rango, i + rango, 1 do
        for j = pos_y - rango, j + rango, 1 do
            if (#mapa[i][j] >= 100) then
                return {posicionX = i, posicionY = j}
            end
        end
    end
    return nil
end



function disparar_al_enemigo()
    return 'p'
end

function crear_accion(pos_x, pos_y)
    local siguiente_mov = proximo_movimiento(pos_x, pos_y)
    local posicion_enemigo = posicion_enemigo_cerca(pos_x, pos_y)
    if (posicion_enemigo) then
        return disparar_al_enemigo()   --avanzar_hacia_enemigo(posicion_enemigo, pos_x, pos_y)
    end
    print(siguiente_mov)
    return siguiente_mov
end




-- Teniendo ya la posicion del enemigo, el jugador lua se tiene que acercar a el
-- siempre en posiciones validas
--[function avanzar_hacia_enemigo(posicion_enemigo, pos_x, pos_y)
--   if (posicion_enemigo.posicionX > pos_x) then
--        if (posicion_enemigo.posicionY > pos_y) then
--            --avanzar hacia adelante y a la derecha, pero tengo que chequear que pueda avanzar porque se tiene que mover
--            -- siempre en posiciones validas
--        else
--            -- avanzo a la derecha y hacia atras
--            --CHEQUEO SI PUEDO
--        end
--   else
--        if (posicion_enemigo.posicionY > pos_y) then
--            --avanzar hacia adelante y a la izquierda, pero tengo que chequear que pueda avanzar porque se tiene que mover
--            -- siempre en posiciones validas
--        else
--            -- avanzo a la izquierda y hacia atras
--           --CHEQUEO SI PUEDO
--        end
--    end
--end
--]

